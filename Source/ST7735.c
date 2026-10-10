#include "../Header/compiler.h"
#include "../Header/main.h"
#include "../Header/HardwareProfile.h"
#include "../Header/Variabili.h"
#include "../Header/ST7735.h"
#include "../Header/font.h"

unsigned char madctl;

void delay_ms(unsigned int sleep_ms);
void delay_us(unsigned int sleep_us);

#ifdef SPI_HW
/*********************************************************
*
*		void sendcomand(char output)
*
*	Permette di inviare i byte al Display in formato COMANDI
*	char output = Contiene il valore da inviare su SPI
***********************************************************/

void sendcomand(unsigned char output)
{
RS_TFT =0;
CS_TFT = 0;

SPIPut1(output);

//for(j=0;j<1;j++);

CS_TFT = 1;
}

/*********************************************************
*
*		void senddata(char output)
*
*	Permette di inviare i byte al Display in formato DATA
*	char output = Contiene il valore da inviare su SPI
***********************************************************/
void senddata(unsigned char output)
{
RS_TFT =1;
CS_TFT = 0;

SPIPut1(output);

//for(j=0;j<1;j++);

CS_TFT = 1;
}

#else

/*********************************************************
*
*		void senddata(char output)
*
*	Permette di inviare un byte simulando SPI
*	char output = Contiene il valore da inviare su SPI
***********************************************************/

void write_spi_byte(unsigned char c)
{
// using software SPI
char x;
for(x=0;x<8;x++)
	{
	LCD_SCK_TFT = 0;       //clock the byte out
	LCD_SDO_TFT = 0;

	if(c & 0x80)
		LCD_SDO_TFT = 1;

	LCD_SCK_TFT = 1;
	c <<= 1;
	}

// using hardware SPI
// spi2Write(cmd);
}

/*********************************************************
*
*		void sendcomand(unsigned char output)
*
*	Permette di inviare i byte al Display in formato COMANDI
*	char output = Contiene il valore da inviare su SPI
***********************************************************/

void sendcomand(unsigned char output)
{
	RS_TFT = 0;
	CS_TFT = 0;
	write_spi_byte(output);
	CS_TFT = 1;
}

/*********************************************************
*
*		void senddata(char output)
*
*	Permette di inviare i byte al Display in formato DATA
*	char output = Contiene il valore da inviare su SPI
***********************************************************/
void senddata(unsigned char output)
{
	RS_TFT = 1;
	CS_TFT = 0;
	write_spi_byte(output);
	CS_TFT = 1;
}
#endif

/******************************************************************
*
*		void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1)
*
*		Definisce Le dimensioni dello Schermo
*		x0 , y0=  Coordinate di partenza
*		x1 , y1=  Coordinate di arrivo
********************************************************************/
void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1)
{
sendcomand(ST7735_CASET);  // column addr set
senddata(0x00);
senddata(x0+OFFSET_X);   // XSTART 
senddata(0x00);
senddata(x1+OFFSET_X);   // XEND

sendcomand(ST7735_RASET);  // row addr set
senddata(0x00);
senddata(y0+OFFSET_Y);    // YSTART
senddata(0x00);
senddata(y1+OFFSET_Y);    // YEND

sendcomand(ST7735_RAMWR);  // write to RAM
}

/******************************************************************
*
*		void ST7735_pushColor(unsigned int color)
*
*		Imposta il colore del pixel per il disegno su Display
********************************************************************/

void ST7735_pushColor(unsigned int color)
{
RS_TFT = 1;
CS_TFT = 0;

#ifdef SPI_HW
	SPIPut1(color >> 8);
	SPIPut1(color);
#else
	write_spi_byte(color >> 8);
	write_spi_byte(color);
#endif
CS_TFT = 1;
}

/******************************************************************
*
*		void ST7735_drawPixel(unsigned char x, unsigned char y, unsigned int color)
*
*	Petmette di accendere un Pixel sullo scehrmo
*	unsigned char x = Coordinata X di Accensione
*	unsigned char y = Coordinata Y di Accensione
*	unsigned int color = Colore del Pixel
********************************************************************/
void ST7735_drawPixel(unsigned char x, unsigned char y, unsigned int color)
{
setAddrWindow(x, y, x-1, y-1);

RS_TFT = 1;
CS_TFT = 0;

#ifdef SPI_HW
	SPIPut1(color >> 8);
	SPIPut1(color);
#else
	write_spi_byte(color >> 8);    
	write_spi_byte(color);   
#endif

CS_TFT = 1;
}

/******************************************************************
*
*				void ST7735_fillScreen(unsigned int color)
*
*	Riempie tutto los chermo di un detemrinato colore
*	unsigned int color = colore da usare per il riempimento
********************************************************************/
void ST7735_fillScreen(unsigned int ScreenColor)
{
unsigned char x, xMAX;
unsigned char y, yMAX;

xMAX=SCREEN_WIDTH;
yMAX=SCREEN_HEIGHT;
setAddrWindow(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

// setup for data
RS_TFT = 1;
CS_TFT = 0;

for (y=0; y < yMAX; y++)
	{
	for (x=0; x < xMAX; x++)
		{
		#ifdef SPI_HW
			SPIPut1(ScreenColor>>8);
			SPIPut1(ScreenColor); 
		#else
			write_spi_byte(ScreenColor>>8);
			write_spi_byte(ScreenColor); 
		#endif

		}
	}

CS_TFT = 1;
}

/******************************************************************
*
*				void Init_ST7735(void)
*
*	Inizializza le impostazione del controllor Video
********************************************************************/

void ST7735_Init(void)
{

LED_RETRO_TFT=1;
RST_TFT = 1;
delay_us(200);
RST_TFT = 0;
delay_us(200);
RST_TFT = 1;

CS_TFT = 0;

sendcomand(ST7735_SWRESET); 	// software reset
delay_us(150);

sendcomand(ST7735_SLPOUT);  	// out of sleep mode
delay_us(500);

sendcomand(ST7735_COLMOD);  	// set color mode
senddata(0x05);        			// 16-bit color
delay_us(10);

sendcomand(ST7735_FRMCTR1);  	// frame rate control - normal mode
senddata(0x01);  				// frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
senddata(0x2C); 
senddata(0x2D); 

sendcomand(ST7735_FRMCTR2);  	// frame rate control - idle mode
senddata(0x01); 				// frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
senddata(0x2C); 
senddata(0x2D); 

sendcomand(ST7735_FRMCTR3);  	// frame rate control - partial mode
senddata(0x01); 				// dot inversion mode
senddata(0x2C); 
senddata(0x2D); 
senddata(0x01); 				// line inversion mode
senddata(0x2C); 
senddata(0x2D); 

sendcomand(ST7735_INVCTR);  	// display inversion control
senddata(0x07); 			 	// no inversion
	
sendcomand(ST7735_PWCTR1);  	// power control
senddata(0xA2);      
senddata(0x02);      			// -4.6V
senddata(0x84);      			// AUTO mode

sendcomand(ST7735_PWCTR2);  	// power control
senddata(0xC5);      			// VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

sendcomand(ST7735_PWCTR3);  	// power control
senddata(0x0A);      			// Opamp current small 
senddata(0x00);      			// Boost frequency

sendcomand(ST7735_PWCTR4);  	// power control
senddata(0x8A);      			// BCLK/2, Opamp current small & Medium low
senddata(0x2A);     

sendcomand(ST7735_PWCTR5);  	// power control
senddata(0x8A);    
senddata(0xEE);     

sendcomand(ST7735_VMCTR1);  	// power control
senddata(0x0E);  

sendcomand(ST7735_INVOFF);    	// don't invert display

sendcomand(ST7735_MADCTL);  	// memory access control (directions)

// http://www.adafruit.com/forums/viewtopic.php?f=47&p=180341

// R and B byte are swapped
// madctl = 0xC8;

// normal R G B order
madctl = 0xC8;					//C0
senddata(madctl);  				// row address/col address, bottom to top refresh

sendcomand(ST7735_COLMOD);  	// set color mode
senddata(0x05);        			// 16-bit color

sendcomand(ST7735_CASET);  				// column addr set
senddata(0x00);
senddata(OFFSET_X);   					// XSTART = 0
senddata(0x00);
senddata(SCREEN_WIDTH-1+OFFSET_X);   	// XEND = 127

sendcomand(ST7735_RASET);  				// row addr set
senddata(0x00);
senddata(OFFSET_Y);    					// YSTART = 0
senddata(0x00);
senddata(SCREEN_HEIGHT-1+OFFSET_Y);    	// YEND = 159

sendcomand(ST7735_GMCTRP1);
senddata(0x0f);
senddata(0x1a);
senddata(0x0f);
senddata(0x18);
senddata(0x2f);
senddata(0x28);
senddata(0x20);
senddata(0x22);
senddata(0x1f);
senddata(0x1b);
senddata(0x23);
senddata(0x37);
senddata(0x00);
senddata(0x07);
senddata(0x02);
senddata(0x10);
sendcomand(ST7735_GMCTRN1);
senddata(0x0f); 
senddata(0x1b); 
senddata(0x0f); 
senddata(0x17); 
senddata(0x33); 
senddata(0x2c); 
senddata(0x29); 
senddata(0x2e); 
senddata(0x30); 
senddata(0x30); 
senddata(0x39); 
senddata(0x3f); 
senddata(0x00); 
senddata(0x07); 
senddata(0x03); 
senddata(0x10); 

sendcomand(ST7735_DISPON);
delay_us(100);

sendcomand(ST7735_NORON); 			 // normal display on
delay_us(10);

CS_TFT= 1;
}

/******************************************************************
*
*		void ST7735_drawString(unsigned char x, unsigned char y, char *c, unsigned int color, unsigned char size)
*
*		Disegna Stringa su Display
*	unsigned char x = Coordinata X di aprtenza del Testo
*	unsigned char y = Coordinata Y di aprtenza del Testo
*	char *c = Puntatore Al testo desiderato	
*	unsigned int color = Colroe con cui deve essere scritto il testo
*	unsigned char size = dimensione Carattere del testo
********************************************************************/

void ST7735_drawString(unsigned char x, unsigned char y, char *c, unsigned int color, unsigned char size)
{
while (c[0] != 0)
	{
	ST7735_drawChar(x, y, c[0], color, size);
	x += size*6;
	c++;
	if (x + 5 >= SCREEN_WIDTH)
		{
		y += 10;
		x = 0;
		}
	}
}

/******************************************************************
*
*	void ST7735_drawChar(unsigned char x, unsigned char y, char c, unsigned int color, unsigned char size)
*
*		Disegna un solo carattere sul Display
*	unsigned char x = Coordinata X di partenza del Testo
*	unsigned char y = Coordinata Y di partenza del Testo
*	char *c 0 Punattore Al testo desiderato	
*	unsigned int color = Colroe con cui deve essere scritto il testo
*	unsigned char size = dimensione Carattere del testo
********************************************************************/

void ST7735_drawChar(unsigned char x, unsigned char y, char c, unsigned int color, unsigned char size)
{
unsigned char i, j;

unsigned char letter = c < 0x52 ? c - 0x20 : c - 0x52;
for (i =0; i<5; i++ )
	{
	unsigned char line = c < 0x52 ? Alpha1[letter*5+i] : Alpha2[letter*5+i];

	for (j = 0; j<8; j++)
		{
		if (line & 0x1)
			{
			if (size == 1) // default size
				ST7735_drawPixel(x+i, y+j, color);
			else 
				{  // big size
				ST7735_fillRect(x+i*size, y+j*size, size, size, color);
				} 
			}
		line >>= 1;
		}
	}
}

/******************************************************************
*
*	void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color) {
*
*	Disegna un Cerchio PIENO sul Display a aprtire dalle Coordinate X0 e Yo, di dimensioni R e colore desiderato
*	unsigned char x0 = Coordinata X di partenza del Testo
*	unsigned char y0 = Coordinata Y di partenza del Testo
*	r = raggio del cerchio 	
*	unsigned int color = Colroe con cui deve essere scritto il testo

********************************************************************/
void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color)
{
int f = 1 - r;
int ddF_x = 1;
int ddF_y = -2 * r;
int x = 0;
int y = r;

ST7735_drawVerticalLine(x0, y0-r, 2*r+1, color);

while (x<y)
	{
	if (f >= 0)
		{
		y--;
		ddF_y += 2;
		f += ddF_y;
		}

	x++;
	ddF_x += 2;
	f += ddF_x;

	ST7735_drawVerticalLine(x0+x, y0-y, 2*y+1, color);
	ST7735_drawVerticalLine(x0-x, y0-y, 2*y+1, color);
	ST7735_drawVerticalLine(x0+y, y0-x, 2*x+1, color);
	ST7735_drawVerticalLine(x0-y, y0-x, 2*x+1, color);
	}
}

/******************************************************************
*
*	void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color) {
*
*	Disegna un Cerchio VUOTO sul Display a aprtire dalle Coordinate X0 e Yo, di dimensioni R e colore desiderato
*	unsigned char x0 = Coordinata X di partenza del Testo
*	unsigned char y0 = Coordinata Y di partenza del Testo
*	r = raggio del cerchio 	
*	unsigned int color = Colroe con cui deve essere scritto il testo

********************************************************************/
void ST7735_drawCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color)
{
int f = 1 - r;
int ddF_x = 1;
int ddF_y = -2 * r;
int x = 0;
int y = r;

ST7735_drawPixel(x0, y0+r, color);
ST7735_drawPixel(x0, y0-r, color);
ST7735_drawPixel(x0+r, y0, color);
ST7735_drawPixel(x0-r, y0, color);

while (x<y)
	{
	if (f >= 0)
		{
		y--;
		ddF_y += 2;
		f += ddF_y;
		}

	x++;
	ddF_x += 2;
	f += ddF_x;

	ST7735_drawPixel(x0 + x, y0 + y, color);
	ST7735_drawPixel(x0 - x, y0 + y, color);
	ST7735_drawPixel(x0 + x, y0 - y, color);
	ST7735_drawPixel(x0 - x, y0 - y, color);
	
	ST7735_drawPixel(x0 + y, y0 + x, color);
	ST7735_drawPixel(x0 - y, y0 + x, color);
	ST7735_drawPixel(x0 + y, y0 - x, color);
	ST7735_drawPixel(x0 - y, y0 - x, color);
	}
}

/**********************************************************
*
*			void ST7735_setRotation(unsigned char m)
*
*	Ottiene il tipo di rotazione di visualizzaione del Display
***************************************************************/

unsigned char ST7735_getRotation(void)
{
	return madctl;
}

/**********************************************************
*
*			void ST7735_setRotation(unsigned char m)
*
*	Imposta il tipo di rotazione di visualizzaione del Display
***************************************************************/

void ST7735_setRotation(unsigned char m)
{
madctl = m;
sendcomand(ST7735_MADCTL);  	// memory access control (directions)
senddata(madctl); 				// row address/col address, bottom to top refresh
}

/**********************************************************
*
*	void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,unsigned int color)
*
*	Disegna un rettangolo VUOTO  aprtire dalle coordinate impostate
*	unsigned char x, y = Coordinata X di partenza del Rettangolo
*	unsigned char w = Lunghezza del rettangolo
*	unsigned char h = Altezza del rettangolo
*	unsigned int color = colore del Rettangolo
***************************************************************/

void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,unsigned int color)
{
// smarter version
ST7735_drawHorizontalLine(x, y, w, color);
ST7735_drawHorizontalLine(x, y+h-1, w, color);
ST7735_drawVerticalLine(x, y, h, color);
ST7735_drawVerticalLine(x+w-1, y, h, color);
}

/**********************************************************
*
*	void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,unsigned int color)
*
*	Disegna un rettangolo PIENO aprtire dalle coordinate impostate
*	unsigned char x, y = Coordinata X di partenza del Rettangolo
*	unsigned char w = Lunghezza del rettangolo
*	unsigned char h = Altezza del rettangolo
*	unsigned int color = colore del Rettangolo
***************************************************************/

void ST7735_fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color)
{
setAddrWindow(x, y, x+w-1, y+h-1);

// setup for data
RS_TFT = 1;
CS_TFT = 0;

for (x=0; x < w; x++)
	{
	for (y=0; y < h; y++)
		{
 		#ifdef SPI_HW
			SPIPut1(color >> 8);
			SPIPut1(color); 
		#else
			write_spi_byte(color >> 8);    
			write_spi_byte(color); 
		#endif
		}
	}

CS_TFT = 1;
}

/************************************************************************************
*
*	void ST7735_drawVerticalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
*
*	Disegna un Linea Verticale a partire dalle coordinate impostate
*	unsigned char x, y = Coordinate di partenza del Rettangolo
*	unsigned char length = Lunghezza della Linea
*	unsigned int color = colore della Linea
***************************************************************************************/

void ST7735_drawVerticalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
{
if (x >= SCREEN_WIDTH)
	return;

if (y+length >= SCREEN_HEIGHT)
	length = SCREEN_HEIGHT-y-1;

ST7735_drawFastLine(x,y,length,color,1);
}

/************************************************************************************
*
*	void ST7735_drawHorizontalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
*
*	Disegna un Linea Orizzontale a partire dalle coordinate impostate
*	unsigned char x, y = Coordinate di partenza del Rettangolo
*	unsigned char length = Lunghezza della Linea
*	unsigned int color = colore della Linea
***************************************************************************************/
void ST7735_drawHorizontalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
{
if (y >= SCREEN_HEIGHT)
	return;
if (x+length >= SCREEN_WIDTH)
	length = SCREEN_WIDTH-x-1;

ST7735_drawFastLine(x,y,length,color,0);
}

void ST7735_drawFastLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color, unsigned char rotflag)
{
unsigned char colorB = color >> 8;
if (rotflag)
	{
	setAddrWindow(x, y, x, y+length);
	}
else
	{
	setAddrWindow(x, y, x+length, y+1);
	}
// setup for data
RS_TFT = 1;
CS_TFT = 0;


while (length--)
	{
	#ifdef SPI_HW
		SPIPut1(colorB);
		SPIPut1(color); 
	#else
		write_spi_byte(colorB);    
		write_spi_byte(color); 
	#endif
	}
CS_TFT = 1;
}

int abs(int val)
{
	return (val > 0) ? val : -val;
}

// bresenham's algorithm - thx wikpedia
void ST7735_drawLine(int x0, int y0, int x1, int y1, unsigned int color)
{
unsigned int dx =2, dy;
unsigned int steep = abs(y1 - y0) > abs(x1 - x0);
int err = dx / 2;
int ystep;


if (steep)
	{
	swap(x0, y0);
	swap(x1, y1);
	}

if (x0 > x1)
	{
	swap(x0, x1);
	swap(y0, y1);
	}


dx = x1 - x0;
dy = abs(y1 - y0);


if (y0 < y1)
	ystep = 1;
else 
	ystep = -1;

for (; x0<=x1; x0++)
	{
	if (steep)
		ST7735_drawPixel(y0, x0, color);
	else
		ST7735_drawPixel(x0, y0, color);

	err -= dy;
	if (err < 0)
		{
		y0 += ystep;
		err += dx;
		}
	}
}

void ST7735_DrawBitmap(unsigned int x, unsigned int y, const unsigned int *image, unsigned int w, unsigned int h)
{
  unsigned int skipC = 0;                      // non-zero if columns need to be skipped due to clipping
  unsigned int originalWidth = w;              // save this value; even if not all columns fit on the screen, the image is still this width in ROM
  unsigned int i = w*(h - 1);

  if((x >= SCREEN_WIDTH) || ((y - h + 1) >= SCREEN_HEIGHT) || ((x + w) <= 0) || (y < 0)){
    return;                             // image is totally off the screen, do nothing
  }
  if((w > SCREEN_WIDTH) || (h > SCREEN_HEIGHT)){    // image is too wide for the screen, do nothing
    //***This isn't necessarily a fatal error, but it makes the
    //following logic much more complicated, since you can have
    //an image that exceeds multiple boundaries and needs to be
    //clipped on more than one side.
    return;
  }
  if((x + w - 1) >= SCREEN_WIDTH){            // image exceeds right of screen
    skipC = (x + w) - SCREEN_WIDTH;           // skip cut off columns
    w = SCREEN_WIDTH - x;
  }
  if((y - h + 1) < 0){                  // image exceeds top of screen
    i = i - (h - y - 1)*originalWidth;  // skip the last cut off rows
    h = y + 1;
  }
  if(x < 0){                            // image exceeds left of screen
    w = w + x;
    skipC = -1*x;                       // skip cut off columns
    i = i - x;                          // skip the first cut off columns
    x = 0;
  }
  if(y >= SCREEN_HEIGHT){                     // image exceeds bottom of screen
    h = h - (y - SCREEN_HEIGHT + 1);
    y = SCREEN_HEIGHT - 1;
  }

  setAddrWindow(x, y-h+1, x+w-1, y);

  for(y=0; y<h; y=y+1)
	{
    for(x=0; x<w; x=x+1)
		{
 		#ifdef SPI_HW
			SPIPut1(image[i] >> 8);
			SPIPut1(image[i]); 
		#else
			write_spi_byte(image[i] >> 8);    
			write_spi_byte(image[i]); 
		#endif


     	 i = i + 1;                        // go to the next pixel
    	}
    i = i + skipC;
    i = i - 2*originalWidth;
  	}
}
