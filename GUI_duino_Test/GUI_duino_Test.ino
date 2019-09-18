





// GUIduino
#include "BIB/GUI_Duino_Test_Params.h" 
#include "GUI_Duino/GUI_Main.h" 





void teste()
{
	LogTerm(F("TESTEeeeeee"));
}

// INTERNA ARDUINO: SETUP
void setup()
{  


    Serial.begin(115200);       // 115200 pois o RFID precisa desta velocidade, para acompanharmos o que ele escreve no serial





	GUI_StartScreen();

	GUI_ResetGenBtn();

	GUI_ResetSelOptions();


	String aTemp[13];

	aTemp[0] = F("1;Marcelo Rocha");
	aTemp[1] = F("2;Andre Marques Silva");
	aTemp[2] = F("3;Ricardo Prado");
	aTemp[3] = F("4;Vera Maria B. Ferraz");
	aTemp[4] = F("5;Paulo do Amaral Rocha");
	aTemp[5] = F("6;Joao da cunha");
	aTemp[6] = F("7;Mateus Vergaro");
	aTemp[7] = F("8;Monica Balog");
	aTemp[8] = F("9;Mariana Balog");
	aTemp[9] = F("10;Gabriel Balog");
	aTemp[10] = F("11;Pires de souza");
	aTemp[11] = F("12;Julio Mesquita");
	aTemp[12] = F("13;Simone de souza viottolon");
	

	GUI_Define_aSelOptions(aTemp, 12);





	//GUI_Render_SelectList(40, 53, 560, 12, Blue, White, 1, White, -1);
	GUI_Render_SelectList(20, 70, 590, 7, Blue, White, 2, White, -1);





	GUI_Render_GenericButton(F("TESTE"), 
								F("Sair"), 
								1, 
								White, 
								Red, 
								8, 
								White, 
								680, 
								25, 
								0, 
								0);


	LogTerm(F("Resultado:"));

	GUI_PrintInTerm_aGenBtn();

	GUI_PrintInTerm_aSelOptions();





}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{
	GUI_TestInterrupt();
}






