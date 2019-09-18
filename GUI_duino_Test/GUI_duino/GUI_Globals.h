


// Width of the chars in the screen
#define ct_GUI_LetterSize_W_Size_0 8  // font size 0
#define ct_GUI_LetterSize_W_Size_1 16  // font size 1
#define ct_GUI_LetterSize_W_Size_2 24  // font size 2
#define ct_GUI_LetterSize_W_Size_3 32  // font size 3

// Heigth of the chars in the screen
#define ct_GUI_LetterSize_H_Size_0 16  // font size 0
#define ct_GUI_LetterSize_H_Size_1 32  // font size 1
#define ct_GUI_LetterSize_H_Size_2 48  // font size 2
#define ct_GUI_LetterSize_H_Size_3 64  // font size 3






// incremental number that keeps track of the count of buttons in a screen. Index
int g_GUI_GenBtn_BtnCount = 0;


// Max buttons allowed in one screen at the same time
#define ct_GUI_MAX_BUTTONS_ONSCREEN 10

// var that hold the coordinates, tag and other info of all buttons in screen
String g_GUI_aGenBtn[ct_GUI_MAX_BUTTONS_ONSCREEN];

// Mas number of itens/options a select can have
#define ct_GUI_MAX_SELECT_OPTIONS 30

// var that hold the coordinates, tag and other info of all options in a select rendered
String g_GUI_aSelOptions[ct_GUI_MAX_SELECT_OPTIONS];

// var that holds the number of the array position of the first line of the select
int g_GUI_SelFirstLineIndex = -1;

// var that holds the number of lines the select has. Has to be global to be used in the callback function and other places
int g_GUI_SelRenderedLines = -1;

// var that holds the parameters of the select rendered, like posx, posy, lines, and others
String g_GUI_SelParams;

// Mas number of lines a select can have, showing in the screen at any given time (the select can have more options. This is the number of lines showing in the screen)
#define ct_GUI_MAX_SELECT_LINES_SHOWING 13

// var that hold the coordinates of the touch area of each option in the select. Get only the coord of the lines showing in the moment
String g_GUI_aSelTouchAreaOpt[ct_GUI_MAX_SELECT_LINES_SHOWING];

// vars that get the touch position
volatile uint16_t g_GUI_Touch_X;
volatile uint16_t g_GUI_Touch_Y;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TOUCH DEBOUNCE
// --------------
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// touch sensibility
#define ct_GUI_BOUNCE_SENSIB_BTN 200


// permitindo que um novo clique ocorra
volatile unsigned long g_GUI_Bounce_time_inicio = 0;
volatile unsigned long g_GUI_Bounce_time_atual = 0;
volatile unsigned long g_GUI_Bounce_time_tempo_passado = 0;

volatile int g_GUI_Bounce_SegundosPassados = 0;
volatile int g_GUI_Bounce_Last_SegundosPassados = 0;


// var que conta o numero de cliques executaados no botao
volatile int g_GUI_Bounce_ContaClick = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










