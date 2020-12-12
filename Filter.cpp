/****************************************************************************************
Versuch B2: Digitale Bildverarbeitung
Bildverarbeitungsalgorithmen für Filter.dll 
*****************************************************************************************/

#include <windows.h>
#include <math.h>

//Beispielfunktion
extern "C" __declspec(dllexport) void BildInvertieren(BYTE*, DWORD, DWORD, int, int, int, int);

//Anpassbare Funktionen
extern "C" __declspec(dllexport) void Funktion1(BYTE*, DWORD, DWORD, int, int, int, int);
extern "C" __declspec(dllexport) void Funktion2(BYTE*, DWORD, DWORD, int, int, int, int);
extern "C" __declspec(dllexport) void Funktion3(BYTE*, DWORD, DWORD, int, int, int, int);
extern "C" __declspec(dllexport) void Funktion4(BYTE*, DWORD, DWORD, int, int, int, int);
extern "C" __declspec(dllexport) void Funktion5(BYTE*, DWORD, DWORD, int, int, int, int);
extern "C" __declspec(dllexport) void Funktion6(BYTE*, BYTE*, DWORD, DWORD, int, int, int, int);

BOOL WINAPI DllEntryPoint(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
 switch (fdwReason)
 {
 case DLL_PROCESS_ATTACH: break;
 case DLL_PROCESS_DETACH: break;
 }
 return TRUE;
}


/**************************************************************************
Hilfsfunktion: InitKanalBuf
---------------------------------------------------------------------------
Liefert einen der Farbkanaele mit einer Randerweiterung von einem Pixel 
  -> pDaten: Zeiger auf erstes Byte des Farbkanals im Gesamtbild
  -> pKanalBuf: Zeiger auf das ersten Byte des seaparaten Farbkanals
---------------------------------------------------------------------------
Achtung! Durch die Randerweiterung wird jede Zeile um 2 Pixel breiter.
Dadurch ergeben sich dann folgende Punktbeziehungen:

pKanalBuf[-dZeile-3] linker oberer Nachbarpunkt
pKanalBuf[-dZeile-2] linker Nachbarpunkt
pKanalBuf[-dZeile-1] linker unterer Nachbarpunkt
pKanalBuf[-1]         oberer Nachbarpunkt
pKanalBuf[0]          Hauptpunkt
pKanalBuf[1]          untere Nachbarpunkt
pKanalBuf[dZeile+1]  rechter oberer Nachbarpunkt
pKanalBuf[dZeile+2]  rechter Nachbarpunkt
pKanalBuf[dZeile+3]  rechter unterer Nachbarpunkt
**************************************************************************/
void InitKanalBuf(BYTE *pDaten, BYTE *pKanalBuf, DWORD dZeile, DWORD dSpalte)
{
	DWORD dBuf1, dBuf2;
	BYTE *pAnfKanalBuf, *pAnfDaten;
	
	pAnfKanalBuf=pKanalBuf;               //Speicheranfang sichern
	pAnfDaten=pDaten;                     //Bilddatenanfang sichern
	pKanalBuf[0]=pDaten[0];               //Randeckpunkt kopieren
	pKanalBuf++;
	//Rand mit erster Bildspalte eines Farbkanals f�llen
	for(dBuf1=0; dBuf1<dZeile; dBuf1++)
	{
		pKanalBuf[dBuf1]=pDaten[dBuf1];  
	}
	pKanalBuf=pKanalBuf+dBuf1;            //Zeiger auf Randeckpunkt setzen
	pKanalBuf[0]=pKanalBuf[-1];           //Randeckpunkt kopieren
	pKanalBuf++;
	//Kanal in den Bildspeicher kopieren, wobei 
	//die Randpixel an beiden Spaltenenden dupliziert werden
	for(dBuf1=0; dBuf1<dSpalte; dBuf1++)   
	{                                     
		pKanalBuf[0]=pDaten[0];              
		pKanalBuf++;
		for(dBuf2=0; dBuf2<dZeile; dBuf2++)
		{
			pKanalBuf[0]=pDaten[0];
			pKanalBuf++;
			pDaten=pDaten++;
		}
		pKanalBuf[0]=pKanalBuf[-1];
		pKanalBuf++;
	}
	//duplizieren der letzten Bildspalte f�r den Rand
	for(dBuf1=0; dBuf1<dZeile+2; dBuf1++)
	{                                     
		pKanalBuf[dBuf1]=pKanalBuf[dBuf1-dSpalte-2];
	}
	pKanalBuf=pAnfKanalBuf;
	pDaten=pAnfDaten;
}

/*********************************************************************
 Beispielfunktion: Bild wird invertiert
 -----------------------------------------
 Funktion ist unabhaengig von den Integerwerten iWert1,..,iWert4,
 die in den Oberflaeche als Parameter A,..,D eingestellt werden
**********************************************************************/
void BildInvertieren(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
					 int iWert1, int iWert2, int iWert3, int iWert4)
{                                     
	BYTE *pAnfDaten;
	DWORD dY;

	pAnfDaten=pDaten;	//Zeigerposition fuer Rueckgabe merken

	//jedes der dZeile*dSpalte*3 Byte durch EXOR-Verk�pfung mit 0xFF invertieren
	for (dY=0; dY<dZeile*dSpalte*3; dY++)
	{
		*pDaten=*pDaten^0xFF;   
		pDaten++;                          
	}
	pDaten=pAnfDaten;	//Zeigerposition fuer Rueckgabe setzen
}


/********************************************************************************
*																				*	
*  Bildverarbeitungsalgorithmen in die nachfolgenden Funktionen implementieren  *
*																				*
********************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//Aufgabe 5.1 : Konvertierung RGB24 -> Graustufen Y
//Weisen Sie die Luminanzwerte Y der einzelnen Pixel dem Speicherbereich des 
//urspr�nglichen Rotkanal zu. 
///////////////////////////////////////////////////////////////////
void Funktion1(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
			   int iWert1, int iWert2, int iWert3, int iWert4)
{                                     
	DWORD dX;
	// ANFANG EIGENER QUELLTEXT
	
	// ENDE EIGENER QUELLTEXT
	
	//Zeigerposition fuer Rueckgabe merken
	BYTE *pAnfDaten;
	pAnfDaten=pDaten; 

	// Wiederhole f�r alle dZeile*dSpalte Pixel
	for(dX=0; dX<dZeile*dSpalte; dX++) 
	{
	
		*(pDaten+2)=(*pDaten)*0.114+(*(pDaten+1))*0.587+(*(pDaten+2))*0.299;			//pDaten +2 um auf Roten Kanal zuzugreifen 
		pDaten=pDaten+3;
	} 
	pDaten=pAnfDaten;

}
///////////////////////////////////////////////////////////////////
//Aufgabe 5.2 : Kantendetektion
//Implementieren Sie eine Kantendetektion unter Verwendung eines
//Laplace-Filters. Zus�tzliche Alternativen �ber "switch(iWert1)"
//sind m�glich und sinnvoll.
///////////////////////////////////////////////////////////////////
void Funktion2(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
			   int iWert1, int iWert2, int iWert3, int iWert4)
{
	// Variablen vereinbaren
	BYTE *pKanalBuf,*pAnfDaten, *pAnfKanalBuf;
	DWORD dBuf,dm, dn;

	// ANFANG EIGENER QUELLTEXT
	int iSumme;	
	// ENDE EIGENER QUELLTEXT
	////////////////////////////////////////////////////////////
	//Filtermasken zur Auswahl �ber Feld A bzw. iWerte1=0 ausw�hlbar
	char Maske[3][3];
	switch(iWert1) 
	{
		case 1: //Laplace (auch Diagonalen)
				Maske[0][0]=1;Maske[0][1]=1;Maske[0][2]=1;
				Maske[1][0]=1;Maske[1][1]=-8;Maske[1][2]=1;
				Maske[2][0]=1;Maske[2][1]=1;Maske[2][2]=1;
				break; 	
		case 2: //Laplace (mitdoppelter Wichtung)
				Maske[0][0]=0;Maske[0][1]=2;Maske[0][2]=0;
				Maske[1][0]=2;Maske[1][1]=-8;Maske[1][2]=2;
				Maske[2][0]=0;Maske[2][1]=2;Maske[2][2]=0;    
				break;  
		case 3: //Laplace invertiert
				Maske[0][0]=-1;Maske[0][1]=-1;Maske[0][2]=-1;
				Maske[1][0]=-1;Maske[1][1]=8;Maske[1][2]=-1;
				Maske[2][0]=-1;Maske[2][1]=-1;Maske[2][2]=-1;
				break;  
		case 4: //Sobel_vertikal
				Maske[0][0]=1;Maske[0][1]=0;Maske[0][2]=-1;
				Maske[1][0]=2;Maske[1][1]=0;Maske[1][2]=-2;
				Maske[2][0]=1;Maske[2][1]=0;Maske[2][2]=-1;
				break; 
		case 5: //Sobel_horizonal
				Maske[0][0]=1;Maske[0][1]=2;Maske[0][2]=1;
				Maske[1][0]=0;Maske[1][1]=0;Maske[1][2]=0;
				Maske[2][0]=-1;Maske[2][1]=-2;Maske[2][2]=-1;
				break;
		default: //Laplace (einfach - hor. & vert.)
				Maske[0][0]=0;Maske[0][1]=1;Maske[0][2]=0;
				Maske[1][0]=1;Maske[1][1]=-4;Maske[1][2]=1;
				Maske[2][0]=0;Maske[2][1]=1;Maske[2][2]=0;
				break; 
	};

	//Zeigerposition fuer Rueckgabe merken
	pAnfDaten=pDaten;

	//Speicher f�r einen Kanal + ein Pixel Rand reservieren
	dBuf=(dZeile+2)*(dSpalte+2);         
	pKanalBuf=(BYTE*)malloc(dBuf);       
	pAnfKanalBuf=pKanalBuf;

	//fuer jeden der drei Farbkanaele
	for (dBuf=0; dBuf<3; dBuf++)
	{
		//Farbkanal aus Gesamtbild auslesen und um ein Randpixel erweitern
		InitKanalBuf(pDaten, pKanalBuf, dZeile, dSpalte);

		// Zeiger auf erstes echtes Subpixel setzen
		pKanalBuf=pKanalBuf+dZeile+3;

		// Filter auf pKanalBuf anwenden und Ergebnis in *pDaten abspeichern
		for(dn=0; dn<dSpalte; dn++)            
		{                                     
			for(dm=0; dm<dZeile; dm++)
			{
				//ANFANG EIGENER QUELLTEXT
				
				*pDaten=*pKanalBuf[-dZeile-3]*Maske[0][0];

				*pDaten=*pDaten+*pKanalBuf[-1]*Maske[0][1];

				*pDaten=*pDaten+*pKanalBuf[dZeile+1]*Maske[0][2];

				*pDaten=*pDaten+*pKanalBuf[-dZeile-2]*Maske[1][0];

				*pDaten=*pDaten+*pKanalBuf[0]*Maske[1][1];

				*pDaten=*pDaten+*pKanalBuf[dZeile+2]*Maske[1][2];

				*pDaten=*pDaten+*pKanalBuf[-dZeile-1]*Maske[2][0];

				*pDaten=*pDaten+*pKanalBuf[1]*Maske[2][1];

				*pDaten=*pDaten+*pKanalBuf[dZeile+3]*Maske[2][2];

				*pDaten=*pDaten/9;
				
				//ENDE EIGENER QUELLTEXT
			}
			// Randerweiterung �berspringen
			pKanalBuf=pKanalBuf+2;
		}
		// Zeiger positionieren fuer naechsten Kanal
		pKanalBuf=pAnfKanalBuf;
		pDaten=pAnfDaten+(dBuf+1)*dZeile*dSpalte;;
	}
	free(pKanalBuf);                    //Bildspeicher freigeben
	pDaten=pAnfDaten;					//Zeiger auf Anfang  setzen
}


///////////////////////////////////////////////////////////////////
//Aufgabe 5.3 : Spiegeln der Bildinformation (oder von Teilen davon)
//Standardaufgabe: horizonal spiegeln
//ZUSATZAUFGABE:
//f�r Parameter A (iWert1):	wenn 1, dann Horizontal spiegeln
//							wenn 2, dann Vertikal spiegeln
//							wenn 3, dann horizontal spiegeln bis zur H�lfte (linke H�lfte)
//							wenn 4, dann horizontal spiegeln bis zur H�lfte (rechte H�lfte)
//							wenn 5, dann vertikal spiegeln bis zur H�lfte (obere H�lfte)
//							wenn 6, dann vertikal spiegeln bis zur H�lfte (untere H�lfte)
///////////////////////////////////////////////////////////////////
void Funktion3(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, int iWert1, int iWert2, int iWert3, int iWert4)
{                                     
	// Variablen vereinbaren
	BYTE *pAnfDaten;
	BYTE temp;
	//ANFANG EIGENER QUELLTEXT
	
	//ENDE EIGENER QUELLTEXT
	// Zeiger auf Bildanfang f�r R�ckgabe merken
	pAnfDaten=pDaten;	
	
	int AnzSpalten, AnzZeilen;		//Größe muss noch festgelegt werden! 

	
	for (DWORD spalte = 0; spalte < AnzSpalten; spalte++)
	{
		for (DWORD zeile = 0; zeile < AnzZeilen/2; zeile++){    // -1 wegen Rundung?? 

			temp=pDaten[zeile][spalte];
			pDaten[zeile][spalte]=pDaten[AnzZeilen-zeile][spalte];
			pDaten[AnzZeilen-zeile][spalte]=temp;
			
		}
	}
	
	//ENDE EIGENER QUELLTEXT
	//Zeiger f�r R�ckgabe setzen
	pDaten=pAnfDaten;
}

///////////////////////////////////////////////////////////////////
//Aufgabe 5.4 : Helligkeitsregelung 
// * unter Verwendung von Look up tables
// * Parameter A (iWert1): Aenderung Rot-Kanal
// * Parameter B (iWert2): Aenderung Gruen-Kanal
// * Parameter C (iWert3): Aenderung Blau-Kanal
// * Parameter D (iWert4): Aenderung Rot-,Gruen- und Blau-Kanal
///////////////////////////////////////////////////////////////////
void Funktion4(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
			   int iWert1, int iWert2, int iWert3, int iWert4)
{                                     

	BYTE *pAnfDaten;
	DWORD dm, dn;
	int i,k;
	BYTE rot[256], blau[256], gruen[256];
 
	//Zeigerposition fuer Rueckgabe merken
	pAnfDaten=pDaten;	

	//1. Look up tables berechnen
	for (i=0;i<256;i++)
	{
		//Parameter fuer rot
		k=i+iWert1+iWert4;
		if (k>255) rot[i]=255;
		else if (k<0) rot[i]=0;
			else rot[i]=k;

		//Parameter fuer gruen
		k=i+iWert2+iWert4;
		if (k>255) gruen[i]=255;
		else if (k<0) gruen[i]=0;
			else gruen[i]=k;

		//Parameter fuer blau
		k=i+iWert3+iWert4;
		if (k>255) blau[i]=255;
		else if (k<0) blau[i]=0;
			else blau[i]=k;
    }

	//Daten aus LUT zuweisen
	for (dm=0; dm<dZeile; dm++)
	{
		for(dn=0; dn<dSpalte; dn++)
		{
			pDaten[0]=rot[pDaten[0]];   
			pDaten[dZeile*dSpalte]=gruen[pDaten[dZeile*dSpalte]];                             
			pDaten[2*dZeile*dSpalte]=blau[pDaten[2*dZeile*dSpalte]];         
			pDaten=pDaten++;
		}
	}
		
	//Zeigerposition fuer Rueckgabe setzen
	pDaten=pAnfDaten;	
}

///////////////////////////////////////////////////////////////////
//Aufgabe 5.5 : eigene Problemstellung realisierbar
///////////////////////////////////////////////////////////////////
void Funktion5(BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
			   int iWert1, int iWert2, int iWert3, int iWert4)
{
	BYTE *pAnfDaten;

	pAnfDaten=pDaten;
	//ANFANG EIGENER QUELLTEXT
	

	//ENDE EIGENER QUELLTEXT}
	pDaten=pAnfDaten;
}



///////////////////////////////////////////////////////////////////
//Funktion 6: Differenzbild Bild 2 = Bild 2 - Bild 1 + Offset 128
///////////////////////////////////////////////////////////////////
void Funktion6(BYTE *pRefDaten, BYTE *pDaten, DWORD dZeile, DWORD dSpalte, 
			   int iWert1, int iWert2, int iWert3, int iWert4)
{
	BYTE *pAnfDaten, *pAnfRefDaten;
	DWORD dBuf, dm, dn;

	pAnfDaten=pDaten;
	pAnfRefDaten=pRefDaten;

	for (dBuf=0; dBuf<3; dBuf++)
	{
		for (dn=0; dn<dSpalte; dn++)
		{
			for(dm=0; dm<dZeile; dm++)
			{
				pDaten[0]=(BYTE)(pDaten[0]-pRefDaten[0]+128);
				pDaten=pDaten++;
				pRefDaten=pRefDaten++;
			}
		}
	}
	pDaten=pAnfDaten;
	pRefDaten=pAnfRefDaten;
}