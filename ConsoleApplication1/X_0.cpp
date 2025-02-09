//X si 0

#include "stdafx.h"                      
#include <stdlib.h>                      // system("cls") 
#include <iostream>
#include <conio.h>                       //pentru _getch;
#include <windows.h>                     //pentru full screen;

using namespace std;

char tabelaJoc[4][4];                     //tabela de joc
int  Alegere = -1;                        //retine ce parte din meniu o sa fie selectat.


HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);          //Pentru marime font consola
void fontsize(int a, int b) {
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}                                    

void initializare(char a[4][4])  ///initializeaza tabla cu 0
{
	int i, j;
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
			a[i][j] = 0;
}

void logo()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fontsize(18,18);
	SetConsoleTextAttribute(hConsole, 11);
	cout << endl << "                                                                     X             X  0000000000000";
	cout << endl << "                                                                      X           X   0           0";
	cout << endl << "                                                                       X         X    0           0";
	cout << endl << "                                                                        X       X     0           0";
	cout << endl << "                                                                         X     X      0           0";
	cout << endl << "                                                                          X   X       0           0";
	cout << endl << "                                                                            X         0           0";
	cout << endl << "                                                                          X   X       0           0";
	cout << endl << "                                                                         X     X      0           0";
	cout << endl << "                                                                        X       X     0           0";
	cout << endl << "                                                                       X         X    0           0";
	cout << endl << "                                                                      X           X   0           0";
	cout << endl << "                                                                     X             X  0000000000000"<< endl << endl << endl;
	SetConsoleTextAttribute(hConsole, 10);
}

void afisareMeniu(int &Alegere)
{
	logo();
	cout << "                                                                            Meniu X si 0" << endl << endl;
	cout << "                                                                          1.Descriere Joc;" << endl;
	cout << "                                                                      2.Player1(X) vs Player2(0);" << endl;
	cout << "                                                                  3.Computer(X) vs Player(0) ~ usor;" << endl;
	cout << "                                                                  4.Player(X) vs Computer(0) ~ usor;" << endl;
	cout << "                                                                  5.Computer(X) vs Player(0) ~ greu;" << endl;
	cout << "                                                                  6.Player(X) vs Computer(0) ~ greu;" << endl;
	cout << "                                                                               0.Iesire;" << endl << endl;
	cout << "                                                                         Introduceti alegerea..."; 
	Alegere = _getch();
	Alegere = Alegere - '0';
}

void afisareDescriere()
{
	logo();
	cout << "                                                                      Descriere joc de  X si 0 : " << endl<<endl;
	cout << "                                  -------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << "                                 |            X ai O (engleza tic-tac-toe) este un joc pentru doi jucatori('X' respectiv '0');                        |" << endl;             
	cout << "                                 |                           Jucatorul cu X va avea mereu prima mutare;                                               |" << endl; 
	cout << "                                 |              Fiecare marcheaza pe rand cate o casuta dintr-un tabel cu 3 linii si 3 coloane;                       |" << endl;
	cout << "                                 |Jucatorul care reuseste primul sa marcheze 3 casute adiacente pe orizontala, verticala sau diagonala castiga jocul. |" << endl;
	cout << "                                  -------------------------------------------------------------------------------------------------------------------- " << endl << endl;
	cout << "                                                       Apasati orice tasta pentru a va intoarce la ecranul principal... ";
}

void afisareTabel(char a[4][4])  ///afiseaza tabla dupa fiecare mutare
{
	system("cls");  
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 13);
	logo();
	int i, j;
	cout << "                                                                            ";
	for (int i = 1; i <= 13; i++)
		cout << "_"; cout << endl;
	cout << "                                                                           ";
	for (int i = 1; i <= 15; i++)
		cout << " "; cout << endl;

	for (i = 1; i <= 3; i++)
	{
		cout << "                                                                            ";
		for (j = 1; j <= 3; j++)
			cout << "| " <<a[i][j] <<' ';
		cout << '|' <<"\n" ;
	}
	cout << "                                                                            ";
	for (int i = 1; i <= 13; i++)
		cout << "_";
	SetConsoleTextAttribute(hConsole, 10);
}

void alege(char a[4][4], char jucatorCurent[1])  /// randul jucatorului lui O sa isi aleaga pozitia pe tabla
{
	int x,y;
	bool miscareCorecta = 0;
	while (!miscareCorecta)
	{
		cout <<endl<< "                                                                            x (linia) =";
		cin>>x;
		cout <<endl<< "                                                                            y (coloana) =";
		cin >> y;
		if (a[x][y] == 0 && (x>=1 && x<=3)  && (y>=1 && y<=3))
		{
			a[x][y] = jucatorCurent[0];
			break;
		}
		else
		{
			cout <<endl<< "                                                                           Miscare invalida!" << "\n";
		}
	}
}

void verif_diagprinc(char a[4][4], char &win)   /// verifica dupa fiecare mutare daca pe diagonala principala sunt 3 de acelasi fel si memoreaza castigatorul
{
	if (a[1][1]==a[2][2] && a[2][2]==a[3][3])
		win = a[1][1];
}

void verif_diagsec(char a[4][4], char &win)    /// verifica dupa fiecare mutare daca pe diagonala secundara sunt 3 de acelasi fel si memoreaza castigatorul
{
	if (a[1][3] == a[2][2] && a[2][2] == a[3][1])
		win = a[1][3];
}

void verif_linii(char a[4][4], char &win) /// verifica dupa fiecare mutare daca pe vreuna dintre linii sunt 3 de acelasi fel si memoreaza castigatorul
{
	for (int i = 1; i <= 3; i++)
	{
		if ( (a[i][1] == a[i][2]) && (a[i][2] == a[i][3]))
		{
			win = a[i][1];
			break;
		}
	}

}

void verif_coloane(char a[4][4], char &w)   /// verifica dupa fiecare mutare daca pe vreuna dintre coloane sunt 3 de acelasi fel si memoreaza castigatorul
{
	for (int j = 1; j <= 3 && w == 0; j++)
	{   
		if ((a[1][j] == a[2][j]) && (a[2][j] == a[3][j]))
		{
			w = a[1][j];
			break;
		}
	}

}

void verificareCastigator(char a[4][4], char &w)
{
	verif_linii(a, w);   ///dupa fiecare alegere/mutare se verifica toate posibilitatile
	if (w == 0)
		verif_coloane(a, w);
	if (w == 0)
		verif_diagprinc(a, w);
	if (w == 0)
		verif_diagsec(a, w);
}

void mutare(char round[1], int &nrTura, char a[4][4])
{
	cout << endl << endl;
	cout << "                                                                            Este randul lui " << round[0] << "." << endl<<endl;
	cout << "                                                            Introduceti coordonatele din tabel pentru mutare: " << endl;
	alege(tabelaJoc, round);
	afisareTabel(tabelaJoc);
	nrTura++;
	if (round[0] == 'O')
		round[0] = 'X';
	else
		round[0] = 'O';
}

void jocPlayerVsPlayer(char round[1])
{
	char win = 0;
	int nrTura = 0;
	bool jocTerminat = 0;
	///win retine simbolul jucatorului castigator
	///round retine ce jucator urmeaza sa realizeze o mutare
	///jocTerminat imi memoreaza daca s-a gasit vreun castigator sau daca toata tabla este plina si este remiza
	///nrTura imi memoreaza numarul de mutari efectuate, iar cand ajunge la 9 afiseaza "Remiza!" si ok=1
	initializare(tabelaJoc); ///initializez tabla
	afisareTabel(tabelaJoc);
	while (!jocTerminat)
	{
		mutare(round, nrTura, tabelaJoc);  ///realizeaza aseara unui element pe tabela
		verificareCastigator(tabelaJoc, win);
		if (win != 0)
		{
			cout << endl << endl << endl<<endl<< "                                                                   !CASTIGATOR!   " << win << "    !CASTIGATOR!     ";
			jocTerminat = 1;
		}
		else if (nrTura == 9 && jocTerminat == 0)
		{
			cout <<endl<<endl<< "                                                                               !REMIZA!     ";
			jocTerminat = 1;
		}
	}
	_getch();
}

void poateCastigaO(int &x, int &y, bool &poate)
{
	poate = false;
	char aux[4][4];
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			aux[i][j] = tabelaJoc[i][j];
	
	for (int i=1;i<=3;i++)
		for (int j = 1; j <= 3; j++)
		{
			if (aux[i][j] == 0)
			{
				aux[i][j] = 'O';
				char win = 0;
				verificareCastigator(aux, win);
				aux[i][j] = 0;
				if (win == 'O')
				{
					poate = true;
					x = i;
					y = j;
					break;
				}
			}
		}
}

void poateCastigaX(int &x, int &y, bool &poate)
{
	poate = false;
	char aux[4][4];
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			aux[i][j] = tabelaJoc[i][j];

	for (int i = 1; i <=3 ; i++)
		for (int j = 1; j <= 3; j++)
		{
			if (aux[i][j] == 0)
			{
				aux[i][j] = 'X';
				char win = 0;
				verificareCastigator(aux, win);
				aux[i][j] = 0;
				if (win != 0)
				{
					poate = true;
					x = i;
					y = j;
					break;
				}
			}
		}
}

void jocComputerVsPlayerEasy(char round[1]) 
{
	initializare(tabelaJoc);
	round[0] = 'O';
	char win = 0;
	tabelaJoc[1][1] = 'X';
	int nrTura = 2;
	while (nrTura < 10 && win==0)
	{
		afisareTabel(tabelaJoc);
		if (nrTura % 2 == 0)
		{
			mutare(round, nrTura, tabelaJoc);
			round[0] = 'O';
			verificareCastigator(tabelaJoc, win);
			if (win != 0)
				break;
		}
		else
		{
			int x = -1, y = -1;
			bool poate, nePus = 1;
			poateCastigaO(x, y, poate);
			if (poate == false)
			{
				for (int i = 1; (i < 4) && (nePus==1); i++)
					for (int j = 1; (j < 4) && (nePus==1); j++)
						if (tabelaJoc[i][j] == 0)
						{
							tabelaJoc[i][j] = 'X';
							nePus = 0;
						}
			}
			else
			{
				tabelaJoc[x][y] = 'X';
			}
			verificareCastigator(tabelaJoc, win);
			nrTura++;
			if (win != 0)
				break;
		}
	}
	afisareTabel(tabelaJoc);
	if (win != 0)
	{
		cout << endl << endl << endl << endl << "                                                                   !CASTIGATOR!   " << win << "    !CASTIGATOR!     ";
	}
	else if (nrTura == 10)
	{
		cout << endl << endl << "                                                                               !REMIZA!     ";
	}
	_getch();
}

void jocPlayerVsComputerEasy(char round[1])
{
	initializare(tabelaJoc);
	round[0] = 'X';
	char win = 0;
	int nrTura = 1;
	while (nrTura < 10 && win == 0)
	{
		afisareTabel(tabelaJoc);
		if (nrTura % 2 == 1)
		{
			mutare(round, nrTura, tabelaJoc);
			verificareCastigator(tabelaJoc, win);
			if (win != 0)
				break;
		}
		else
		{
			if (tabelaJoc[3][1] == 'X' && tabelaJoc[3][2] == 'X' && tabelaJoc[3][3] == 0)                     //SOLUTIE PENTRU BUG-UL ENUNTAT SUB SUBPROGRAM.
			{                                                                                                 
				tabelaJoc[3][3] = 'O';            
				verificareCastigator(tabelaJoc, win);
				nrTura++;
				round[0] = 'X';
				if (win != 0)
					break;
			}
			else
				if (tabelaJoc[3][1] == 'X' && tabelaJoc[3][3] == 'X' && tabelaJoc[3][2] == 0)
				{
					tabelaJoc[3][2] = 'O';
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
			else
				if(tabelaJoc[3][2] == 'X' && tabelaJoc[3][3] == 'X' && tabelaJoc[3][1] == 0)
				{
					tabelaJoc[3][1] = 'O';
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
			else
				if (tabelaJoc[1][3] == 'X' && tabelaJoc[2][3] == 'X' && tabelaJoc[3][3] == 0)
				{
					tabelaJoc[3][3] = 'O';
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
			else
				if (tabelaJoc[2][3] == 'X' && tabelaJoc[3][3] == 'X' && tabelaJoc[1][3] == 0)
				{
					tabelaJoc[1][3] = 'O';
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
			else
				if (tabelaJoc[1][3] == 'X' && tabelaJoc[3][3] == 'X' && tabelaJoc[2][3] == 0)
				{
					tabelaJoc[2][3] = 'O';
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
			else                                                                                  //PANA AICI.
				{
					int x = -1, y = -1;
					bool poate = false;
					poateCastigaX(x, y, poate);
					if (poate == false)
					{
						bool nePus = 1;
						for (int i = 1; (i < 4) && (nePus == 1); i++)
							for (int j = 1; (j < 4) && (nePus == 1); j++)
								if (tabelaJoc[i][j] == 0)
								{
									tabelaJoc[i][j] = 'O';
									nePus = 0;
								}
					}
					else
					{
						tabelaJoc[x][y] = 'O';
					}
					verificareCastigator(tabelaJoc, win);
					nrTura++;
					round[0] = 'X';
					if (win != 0)
						break;
				}
		   }
	}
	afisareTabel(tabelaJoc);
	if (win != 0)
	{
		cout << endl << endl << endl << endl << "                                                                   !CASTIGATOR!   " << win << "    !CASTIGATOR!     ";
	}
	else if (nrTura == 10)
	{
		cout << endl << endl << "                                                                               !REMIZA!     ";
	}
	_getch();
}

void jocComputerVsPlayerHard(char round[1]) 
{
	initializare(tabelaJoc);
	tabelaJoc[3][3] = 'X';                       //Prima mutare a C. va fi mereu in coltul din dreapta sus
	char win = 0;
	round[0] = 'O';
	int nrTura = 2;
	afisareTabel(tabelaJoc);
	mutare(round, nrTura, tabelaJoc);
	if (tabelaJoc[2][2] == 'O')                  //Daca pozitia centrala este ocupata de O dupa prima sa mutare atunci
	{
		tabelaJoc[1][1] = 'X';                   // C. va marca coltul din stanga sus
		nrTura++;
		round[0] = 'O';
		afisareTabel(tabelaJoc);
		mutare(round, nrTura, tabelaJoc);
		while (nrTura <= 9 && win==0)           // In acest moment, calculatorul va juca pe greseala O, daca O joaca corect, meciul se va termina cu remiza;
		{
			if (nrTura % 2 == 1)
			{
				int x=-1, y=-1;
				bool poate;
				poateCastigaX(x, y, poate);
				if (poate)
				{
					win = 'X';
					tabelaJoc[x][y] = 'X';
					break;
				}
				else
				{
					poateCastigaO(x, y, poate);
					tabelaJoc[x][y] = 'X';
					verificareCastigator(tabelaJoc, win);
					if (win != 0)
						break;
					nrTura++;
				}
				afisareTabel(tabelaJoc);
			}
			else
			{
				round[0] = 'O';
				mutare(round, nrTura, tabelaJoc);
			}
		}
	}
	else
	{ //Altfel, C. se va asigura ca nu va putea sa castige O, blocand sansele acestuia, dar in acelasi timp cautand o posibila strategie pentru a castiga;
		if (tabelaJoc[1][3] == 0 && tabelaJoc[2][3] == 0 && tabelaJoc[2][1] == 0)
			tabelaJoc[1][3] = 'X';
		else
			tabelaJoc[3][1] = 'X';
		nrTura++;
		round[0] = 'O';
		afisareTabel(tabelaJoc);
		mutare(round, nrTura, tabelaJoc);
		bool poate;
		int x = -1, y = -1;
		poateCastigaX(x, y, poate);
		if (tabelaJoc[2][3] == 0 && tabelaJoc[1][3] == 'X')
		{
			x = 2; y = 3; poate = true;
		}
		else if (tabelaJoc[3][1] == 'X' && tabelaJoc[3][2] == 0)
		{
			x = 3; y = 2; poate = true;
		}
		if (poate)
		{
			win = 'X';
			tabelaJoc[x][y] = 'X';
		}
		else
		{
			if (tabelaJoc[1][1] == 0)
				tabelaJoc[1][1] = 'X';
			else
				if (tabelaJoc[1][3] == 0)
					tabelaJoc[1][3] = 'X';
				else
					tabelaJoc[3][1] = 'X';
			nrTura++;
			round[0] = 'O';
			afisareTabel(tabelaJoc);
			mutare(round, nrTura, tabelaJoc);
			while (nrTura <= 9 && win == 0)
			{
				if (nrTura % 2 == 1)
				{
					int x = -1, y = -1;
					bool poate;
					poateCastigaX(x, y, poate);
					if (poate)
					{
						win = 'X';
						tabelaJoc[x][y] = 'X';
						break;
					}
					else
					{
						poateCastigaO(x, y, poate);
						tabelaJoc[x][y] = 'X';
						verificareCastigator(tabelaJoc, win);
						if (win != 0)
							break;
						nrTura++;
					}
					afisareTabel(tabelaJoc);
				}
				else
				{
					round[0] = 'O';
					mutare(round, nrTura, tabelaJoc);
				}
			}
		}
	}

	afisareTabel(tabelaJoc);
	if (win != 0)
	{
		cout << endl << endl << endl << endl << "                                                                   !CASTIGATOR!   " << win << "    !CASTIGATOR!     ";
	}
	else if (nrTura == 10)
	{
		cout << endl << endl << "                                                                               !REMIZA!     ";
	}
	_getch();
}

void jocPlayerVsComputerHard(char round[1])
{
	initializare(tabelaJoc);
	char win = 0;
	round[0] = 'X';
	int nrTura = 1;
	afisareTabel(tabelaJoc);
	mutare(round, nrTura, tabelaJoc);
	if (tabelaJoc[2][2] == 0)
	{
		nrTura++;
		tabelaJoc[2][2] = 'O';
		round[0] = 'X';
		afisareTabel(tabelaJoc);
		mutare(round, nrTura, tabelaJoc);
		int x = -1, y = -1;
		bool poate = false;
		poateCastigaX(x, y, poate);
		//BUG
		if (tabelaJoc[1][3] == tabelaJoc[2][3] && tabelaJoc[1][3] != 0 && tabelaJoc[3][3] == 0)
		{
			x = 3; y = 3; poate = true;
		}
		if (tabelaJoc[1][3] == tabelaJoc[3][3] && tabelaJoc[1][3] != 0 && tabelaJoc[2][3] == 0)
		{
			x = 2; y = 3; poate = true;
		}
		if (tabelaJoc[2][3] == tabelaJoc[3][3] && tabelaJoc[2][3] != 0 && tabelaJoc[1][3] == 0)
		{
			x = 1; y = 3; poate = true;
		}
		if (tabelaJoc[3][1] == tabelaJoc[3][2] && tabelaJoc[3][2] != 0 && tabelaJoc[3][3] == 0)
		{
			x = 3; y = 3; poate = true;
		}
		if (tabelaJoc[3][3] == tabelaJoc[3][2] && tabelaJoc[3][3] != 0 && tabelaJoc[3][1] == 0)
		{
			x = 3; y = 1; poate = true;
		}
		if (tabelaJoc[3][3] == tabelaJoc[3][1] && tabelaJoc[3][3] != 0 && tabelaJoc[3][2] == 0)
		{
			x = 3; y = 2; poate = true;
		} 
		//BUG
		if (poate)
			tabelaJoc[x][y] = 'O';
		else
			{
				if (tabelaJoc[1][2] == 0)
					tabelaJoc[1][2] = 'O';
				else
					tabelaJoc[2][1] = 'O';
			}  
		poate = false;
		round[0] = 'X';
	    nrTura++;
		afisareTabel(tabelaJoc);
		mutare(round, nrTura, tabelaJoc);
		while (win == 0 && nrTura != 10)
			{
				if (nrTura % 2 == 1)
				{
					round[0] = 'X';
					afisareTabel(tabelaJoc);
					mutare(round, nrTura, tabelaJoc);
				}
				else
				{
					poate = false;
					poateCastigaO(x, y, poate);
					if (poate)
					{
						win = 'O';
						tabelaJoc[x][y] = 'O';
					}
					else
					{
						poateCastigaX(x, y, poate);
						if (poate)
							tabelaJoc[x][y] = 'O';
						else
						{
							bool pus = true;
							for (int i = 1; i <= 3 && pus; i++)
								for (int j = 1; j <= 3 && pus; j++)
									if (tabelaJoc[i][j] == 0)
									{
										tabelaJoc[i][j] = 'O';
										pus = false;
									}
						}
					}
					nrTura++;
					verificareCastigator(tabelaJoc, win);
					if (nrTura == 10 || win!=0)
						break;
				}
			}
	}        //Problema este impartita in doua cazuri, daca X pune pe centru sau oriunde altundeva.
	else
	{
		nrTura++;
		tabelaJoc[1][1] = 'O';
		afisareTabel(tabelaJoc);
		round[0] = 'X';
		mutare(round, nrTura, tabelaJoc);
		bool poate; int x = -1, y = -1;
		while (win == 0 && nrTura != 10)
		{
			if (nrTura % 2 == 1)
			{
				round[0] = 'X';
				afisareTabel(tabelaJoc);
				mutare(round, nrTura, tabelaJoc);
			}
			else
			{
				poate = false;
				poateCastigaO(x, y, poate);
				if (poate)
				{
					win = 'O';
					tabelaJoc[x][y] = 'O';
				}
				else
				{
					poateCastigaX(x, y, poate);
					if (poate)
						tabelaJoc[x][y] = 'O';
					else
					{
						bool pus = true;
						for (int i = 1; i <= 3 && pus; i++)
							for (int j = 1; j <= 3 && pus; j++)
								if (tabelaJoc[i][j] == 0)
								{
									tabelaJoc[i][j] = 'O';
									pus = false;
								}
					}
				}
				nrTura++;
				verificareCastigator(tabelaJoc, win);
				if (nrTura == 10 || win != 0)
					break;
			}
		}
	}

	afisareTabel(tabelaJoc);
	if (win != 0)
	{
		cout << endl << endl << endl << endl << "                                                                   !CASTIGATOR!   " << win << "    !CASTIGATOR!     ";
	}
	else if (nrTura == 10)
	{
		cout << endl << endl << "                                                                               !REMIZA!     ";
	}
	_getch();
}

int main()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);  //Seteaza aplicatia pe full screen.
	while (Alegere!=0)
	{
		 system("cls");
	 	 afisareMeniu(Alegere);
		 switch (Alegere)
		 {
		  case 1:
		  {
			system("cls");
			afisareDescriere();
			_getch();
			system("cls");
			Alegere = -1;
			break;
		  }
		  case 2:
		  {
			system("cls");
			char round[1];
			round[0] = 'X';
			jocPlayerVsPlayer(round);
			_getch();
			system("cls");
			Alegere = -1;
			break;
		  }
		  case 3:
		  {
			  system("cls");
			  char round[1];
			  jocComputerVsPlayerEasy(round);
			  system("cls");
			  Alegere = -1;
			  break;
		  }
		  case 4:
		  {
			  system("cls");
			  char round[1];
			  jocPlayerVsComputerEasy(round);
			  system("cls");
			  Alegere = -1;
			  break;
		  }
		  case 5:
		  {
			  system("cls");
			  char round[1];
			  jocComputerVsPlayerHard(round);
			  system("cls");
			  Alegere = -1;
			  break;
		  }
		  case 6:
		  {
			  system("cls");
			  char round[1];
			  jocPlayerVsComputerHard(round);
			  system("cls");
			  Alegere = -1;
			  break;
		  }
		}
	}
}