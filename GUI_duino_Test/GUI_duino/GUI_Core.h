


void GUI_StartScreen()
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{

		pinMode(GUI_RA8875_INT, INPUT);
		digitalWrite(GUI_RA8875_INT, HIGH);


		GUI_tft.begin(RA8875_800x480);  

		//tft.fillScreen(RA8875_BLACK);//fill screen black
		//tft.changeMode(TEXT);
		//tft.setCursor(0,0);

			
	

		#ifdef GUI_LIB_IN_USE_Adafruit_RA8875


			
			GUI_tft.displayOn(true);
			GUI_tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
			GUI_tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
			GUI_tft.PWM1out(255);
			//GUI_tft.fillScreen(RA8875_BLACK);

			/* Switch to text mode */  
			GUI_tft.textMode();

			
		#elif GUI_LIB_IN_USE_RA8875

			GUI_tft.touchBegin(GUI_RA8875_INT);//enable Touch support!

		#endif		

		GUI_tft.touchEnable(true);
	}

}




void GUI_SetFontSize(int FontSize)
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		GUI_tft.textEnlarge(FontSize);
		
	#elif GUI_LIB_IN_USE_RA8875

		GUI_tft.setFontScale(FontSize);

		//GUI_tft.setFontSize(X16,true);

	#endif	
}


bool GUI_touchDetect()
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		return GUI_tft.touched();
		
	#elif GUI_LIB_IN_USE_RA8875

		return GUI_tft.touchDetect();

	#endif	
}


bool GUI_touchReadPixel(uint16_t *x, uint16_t *y)
{
	#ifdef GUI_LIB_IN_USE_Adafruit_RA8875

		return GUI_tft.touchRead(x, y);
		
	#elif GUI_LIB_IN_USE_RA8875

		GUI_tft.touchReadPixel(x, y);
		return true;		

	#endif	
}




void GUI_ClearScreen()
{
	delay(100);
	GUI_tft.fillScreen(RA8875_BLACK);
}




void GUI_ResetGenBtn()
{

	g_GUI_GenBtn_BtnCount = 0;
	
	for (int t = 0 ; t <= ct_GUI_MAX_BUTTONS_ONSCREEN - 1 ; t++)
	{
		g_GUI_aGenBtn[t] = F("");
	}
}


void GUI_PrintInTerm_aGenBtn()
{
	int EncontrouDados = 0;

	for (int z = 0 ; z <= ct_GUI_MAX_BUTTONS_ONSCREEN - 1 ; z++)
	{
		if (g_GUI_aGenBtn[z] != F(""))
		{
			EncontrouDados = 1;
			LogTerm( String(F("g_GUI_aGenBtn[")) + String(z) + String(F("] = ")) + g_GUI_aGenBtn[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("g_GUI_aGenBtn is empty"));
	}
}



void GUI_ResetSelOptions()
{
	for (int t = 0 ; t <= ct_GUI_MAX_SELECT_OPTIONS - 1 ; t++)
	{
		g_GUI_aSelOptions[t] = F("");
	}
}


void GUI_PrintInTerm_aSelOptions()
{
	int EncontrouDados = 0;

	for (int z = 0 ; z <= ct_GUI_MAX_SELECT_OPTIONS - 1 ; z++)
	{
		if (g_GUI_aSelOptions[z] != F(""))
		{
			EncontrouDados = 1;
			LogTerm( String(F("g_GUI_aSelOptions[")) + String(z) + String(F("] = ")) + g_GUI_aSelOptions[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("g_GUI_aSelOptions is empty"));
	}
}


void GUI_Define_aSelOptions(String aOptions[], int OptionsTotalCount)
{
	int EncontrouDados = 0;

	//int OptionsTotalCount = 3;

	g_GUI_SelFirstLineIndex = 0;


	for (int z = 0 ; z <= OptionsTotalCount; z++)
	{
		g_GUI_aSelOptions[z] = F("");
	}


	for (int z = 0 ; z <= OptionsTotalCount; z++)
	{
		if (aOptions[z] != F(""))
		{
			EncontrouDados = 1;

			g_GUI_aSelOptions[z] = aOptions[z];

			//LogTerm( String(F("g_GUI_aSelOptions[")) + String(z) + String(F("] = ")) + g_GUI_aSelOptions[z] );
		}
	}

	if (EncontrouDados == 0)
	{
		LogTerm(F("passed array aOptions is empty"));
	}
}






void GUI_CheckTouch_SelectList()
{

	int x;


	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		if (GUI_touchDetect())
		{


			GUI_touchReadPixel(&g_GUI_Touch_X, &g_GUI_Touch_Y);
		
			// read tuff


			for (x = 0 ; x <= g_GUI_SelRenderedLines - 1; x++)
			{

				if (g_GUI_aSelTouchAreaOpt[x] != F(""))
				{

					String PosX_Opt = 	getValue(g_GUI_aSelTouchAreaOpt[x], ';', 0);
					String PosY_Opt = 	getValue(g_GUI_aSelTouchAreaOpt[x], ';', 1);
					String SizeW = 		getValue(g_GUI_aSelTouchAreaOpt[x], ';', 2);
					String SizeH = 		getValue(g_GUI_aSelTouchAreaOpt[x], ';', 3);


					//GUI_tft.fillRect(PosX_Opt.toInt() + 50, PosY_Opt.toInt() + x * 0, SizeW.toInt() - 50, SizeH.toInt(), x % 2 ? Yellow : Orange);


					if (g_GUI_Touch_X >= PosX_Opt.toInt() && g_GUI_Touch_X <= SizeW.toInt() + PosX_Opt.toInt())  
					{

						if (g_GUI_Touch_Y >= PosY_Opt.toInt() && g_GUI_Touch_Y <= SizeH.toInt() + PosY_Opt.toInt()) 
						{




							// DEBOUNCE -- START ----------------------------------------------

							g_GUI_Bounce_ContaClick++;
							

							if (g_GUI_Bounce_ContaClick == 1)
							{
								// DEBOUNCE -- ACTION - START ----------------------------------------------

			
								LogTerm(String(F("OPTION PRESSED - ")) + String(x));

								
								String ID_Option = getValue(g_GUI_aSelOptions[x + g_GUI_SelFirstLineIndex], ';', 0);
								String Text_Option = getValue(g_GUI_aSelOptions[x + g_GUI_SelFirstLineIndex], ';', 1);

								// render retangle to show option selected


								//int PosX_Opt_text = -1;
								//int PosY_Opt_text = -1;
								
								//int Size_W_Opt_text = -1;
								//int Size_H_Opt_text = -1;
								

								//int FontSize = -1;
								uint16_t TextColor = -1; 
								uint16_t TextBackColor = -1;
								//int16_t SizeW = -1;
								int _SizeBtnSroll_W_UP = -1;
								int _CharSizeW = -1;
								//int _CharSizeH = -1;
								//int16_t Lines = -1;
								//int16_t PosX = -1;
								//int16_t PosY = -1;
								//int MarginTop = -1;
								//int MarginLeft = -1;
								//uint16_t FillColor = -1;
								//int Calc_H = -1;


								//LogTerm(String(F("g_GUI_SelParams = ")) + g_GUI_SelParams);

								//FontSize 			= String(getValue(g_GUI_SelParams, ';', 0)).toInt();
								TextColor 			= String(getValue(g_GUI_SelParams, ';', 1)).toInt();
								TextBackColor 		= String(getValue(g_GUI_SelParams, ';', 2)).toInt();
								//SizeW 				= String(getValue(g_GUI_SelParams, ';', 3)).toInt();
								_SizeBtnSroll_W_UP 	= String(getValue(g_GUI_SelParams, ';', 4)).toInt();
								_CharSizeW 			= String(getValue(g_GUI_SelParams, ';', 5)).toInt();
								//_CharSizeH 			= String(getValue(g_GUI_SelParams, ';', 6)).toInt();
								//Lines 				= String(getValue(g_GUI_SelParams, ';', 7)).toInt();
								//PosX 				= String(getValue(g_GUI_SelParams, ';', 8)).toInt();
								//PosY 				= String(getValue(g_GUI_SelParams, ';', 9)).toInt();
								//Calc_H 				= String(getValue(g_GUI_SelParams, ';', 10)).toInt();
								//FillColor 			= String(getValue(g_GUI_SelParams, ';', 11)).toInt();
								//MarginLeft 			= String(getValue(g_GUI_SelParams, ';', 12)).toInt();
								//MarginTop 			= String(getValue(g_GUI_SelParams, ';', 13)).toInt();


								//int MaxNumberCharOpt = (SizeW.toInt() - _SizeBtnSroll_W_UP.toInt()) / _CharSizeW.toInt();
								int MaxNumberCharOpt = 20;

								GUI_tft.fillRect(PosX_Opt.toInt(), PosY_Opt.toInt() + x * 0, SizeW.toInt(), SizeH.toInt(), White);

								delay(200);

								GUI_tft.fillRect(PosX_Opt.toInt(), PosY_Opt.toInt() + x * 0, SizeW.toInt(), SizeH.toInt(), Blue);

								GUI_tft.setTextColor(White, TextBackColor);
								//GUI_tft.setCursor (PosX_Opt, PosY_Opt); 
								//GUI_tft.print (Left(Text_Option, MaxNumberCharOpt));



								GUI_Touch_SelectCallBackFunc(ID_Option);

								/*
								if (btnGen_TAG == F("SEL1_SCROLL_UP"))
								{
	


								}
								*/

							


						


								// DEBOUNCE -- ACTION - END ----------------------------------------------

								g_GUI_Bounce_time_inicio = millis();

							}




							g_GUI_Bounce_time_atual = millis();
							g_GUI_Bounce_time_tempo_passado = g_GUI_Bounce_time_atual - g_GUI_Bounce_time_inicio;

							g_GUI_Bounce_SegundosPassados = floor(g_GUI_Bounce_time_tempo_passado / 1000);

							//LogTerm(g_GUI_Bounce_time_tempo_passado);

							if (g_GUI_Bounce_SegundosPassados != g_GUI_Bounce_Last_SegundosPassados)
							{
								//LogTerm(time_tempo_passado);
							}



							if (g_GUI_Bounce_time_tempo_passado >= ct_GUI_BOUNCE_SENSIB_BTN)
							{

								g_GUI_Bounce_ContaClick = 0;		

							}

							g_GUI_Bounce_Last_SegundosPassados = g_GUI_Bounce_SegundosPassados;

							// DEBOUNCE -- END ----------------------------------------------





						}

					}



				}


			}	

		}

	}

}


void GUI_CheckTouch_Button()
{

	if (String(GUI_SCREEN_HARDWARE) == String(F("ER-TFTM070-5")))
	{  

		if (GUI_touchDetect())
		{


			//TELA_LogTerm_XY();
			//LogTerm(F("TELA_VerificaTouch_ADMIN_NOVO_CARD");

			GUI_touchReadPixel(&g_GUI_Touch_X, &g_GUI_Touch_Y);
		
			/*


			/*
		    gaBotoesGenTela[Index - 1] = String(Index) 	+ String(F(";")) + 
		    							 TAG 			+ String(F(";")) + 
		    							 Texto 			+ String(F(";")) + 
		    							 String(PosX) 	+ String(F(";")) + 
		    							 String(PosY) 	+ String(F(";")) + 
		    							 String(W) 		+ String(F(";")) + 
		    							 String(H);

			*/



			for (int ContaBotaoGen = 1 ; ContaBotaoGen <= ct_GUI_MAX_BUTTONS_ONSCREEN ; ContaBotaoGen++)
			{
				if (g_GUI_aGenBtn[ContaBotaoGen - 1] != F(""))
				{
				

					//LogTerm( String(F("g_GUI_aGenBtn[")) + String(ContaBotaoGen - 1) + String(F("] = ")) + g_GUI_aGenBtn[ContaBotaoGen - 1] );

					String btnGen_TAG = 	getValue(g_GUI_aGenBtn[ContaBotaoGen - 1], ';', 1);
					String btnGen_PosX = 	getValue(g_GUI_aGenBtn[ContaBotaoGen - 1], ';', 3);
					String btnGen_PosY = 	getValue(g_GUI_aGenBtn[ContaBotaoGen - 1], ';', 4);
					String btnGen_W = 		getValue(g_GUI_aGenBtn[ContaBotaoGen - 1], ';', 5);
					String btnGen_H = 		getValue(g_GUI_aGenBtn[ContaBotaoGen - 1], ';', 6);

					/*

					LogTerm(String(F("btnGen_TAG = ")) + btnGen_TAG);
					LogTerm(String(F("btnGen_PosX = ")) + btnGen_PosX);
					LogTerm(String(F("btnGen_PosY = ")) + btnGen_PosY);
					LogTerm(String(F("btnGen_W = ")) + btnGen_W);
					LogTerm(String(F("btnGen_H = ")) + btnGen_H);
					
					LogTerm(String(F("===============================")));

					*/



		
					if (g_GUI_Touch_X >= btnGen_PosX.toInt() && g_GUI_Touch_X <= btnGen_W.toInt() + btnGen_PosX.toInt())  
					{

						if (g_GUI_Touch_Y >= btnGen_PosY.toInt() && g_GUI_Touch_Y <= btnGen_H.toInt() + btnGen_PosY.toInt()) 
						{




							// DEBOUNCE -- START ----------------------------------------------

							g_GUI_Bounce_ContaClick++;
							

							if (g_GUI_Bounce_ContaClick == 1)
							{
								// DEBOUNCE -- ACTION - START ----------------------------------------------

			
								LogTerm(String(F("BUTTON PRESSED - ")) + String(ContaBotaoGen) + String(F(" ")) + String(F("(")) + btnGen_TAG + String(F(")"))  );


								// test if buttns are internal buttons like the ones in the select list
								if (btnGen_TAG == F("SEL1_SCROLL_UP"))
								{
									//LogTerm(F("xSEL1_SCROLL_UP"));


									if (g_GUI_SelFirstLineIndex - 1 >= 0)
									{
										g_GUI_SelFirstLineIndex--;
										GUI_Render_RefreshSelectOpt();
									}

								}
								else if (btnGen_TAG == F("SEL1_SCROLL_DOWN"))
								{
									//LogTerm(F("xSEL1_SCROLL_DOWN"));

									if (g_GUI_SelFirstLineIndex + 1 + g_GUI_SelRenderedLines < ct_GUI_MAX_SELECT_OPTIONS)
									{
										g_GUI_SelFirstLineIndex++;
										GUI_Render_RefreshSelectOpt();
									}

								}
								else
								{
									GUI_Touch_BtnCallBackFunc(btnGen_TAG);
								}


								


						


								// DEBOUNCE -- ACTION - END ----------------------------------------------

								g_GUI_Bounce_time_inicio = millis();

							}


							g_GUI_Bounce_time_atual = millis();
							g_GUI_Bounce_time_tempo_passado = g_GUI_Bounce_time_atual - g_GUI_Bounce_time_inicio;

							g_GUI_Bounce_SegundosPassados = floor(g_GUI_Bounce_time_tempo_passado / 1000);

							//LogTerm(g_GUI_Bounce_time_tempo_passado);

							if (g_GUI_Bounce_SegundosPassados != g_GUI_Bounce_Last_SegundosPassados)
							{
								//LogTerm(time_tempo_passado);
							}



							if (g_GUI_Bounce_time_tempo_passado >= ct_GUI_BOUNCE_SENSIB_BTN)
							{

								g_GUI_Bounce_ContaClick = 0;		

							}

							g_GUI_Bounce_Last_SegundosPassados = g_GUI_Bounce_SegundosPassados;

							// DEBOUNCE -- END ----------------------------------------------



						}

					}










				}
			}	    							 





		}

	}

}




void GUI_TestInterrupt()
{

	GUI_CheckTouch_Button();
	GUI_CheckTouch_SelectList();

}




