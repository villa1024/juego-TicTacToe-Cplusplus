#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void AltEnter()
{
    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}

void gotoxy (int x, int y) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}
void OcultarCursor() {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon,&cci);
}
int color[8] = {
	0x009, // azul
	0x00E, // amarillo
	0x00C, // rojo
	0x002, // verde
	0x00B, // celeste
	0x005, // morado
	0x00F, // rosado
	0,
};
void setColor (int color) {
	static HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
class Flecha {
		char cabeza = (char)16;
		char tronco = (char)297;
		int x;
		int y;
	public:
		Flecha (int x_, int y_): x(x_),y(y_) {}
		void DibujarFlecha();
		void MoverFlecha(char tecla_);
		void BorrarFlecha();
		int GetX() { return x; }
		int GetY() { return y; }
};
void Flecha::DibujarFlecha() {
	gotoxy(x,y); cout << cabeza;
	gotoxy(x-1,y); cout << tronco;
	gotoxy(x-2,y); cout << tronco;
}
void Flecha::BorrarFlecha() {
	gotoxy(x,y); cout << " ";
	gotoxy(x-1,y); cout << " ";
	gotoxy(x-2,y); cout << " ";
}
void Flecha::MoverFlecha(char tecla_) {
	BorrarFlecha();
	if (tecla_ == 'w' && y > 9) y -= 20;
	else if (tecla_ == 's' && y < 49) y += 20;
	else if (tecla_ == 'd' && x < 88) x += 40;
	else if (tecla_ == 'a' && x > 8) x -= 40;
	DibujarFlecha();
}
void DibujarMapa() {
	//for (int j=1; j < 60; ++j) {
	//	for (int i=0; i < 60; ++i) {
	//		gotoxy(i,j); cout << (char)475;
	//	}
	for (int j=1; j < 55; ++j) {
		gotoxy(40,j); cout << (char)475;
		gotoxy(80,j); cout << (char)475;
	}
	for (int i=2; i < 130; ++i) {
		gotoxy(i,20); cout << (char)475;
		gotoxy(i,38); cout << (char)475;
	}
}
class X {
		char cuerpo = '*';
		int x;
		int y;
	public:
		X() {}
		int GetX() { return x; }
		int GetY() { return y; }
		void DibujarX(int cX, int cY); 
		void BorrarX();	
};
void X::DibujarX(int cX, int cY) {
	gotoxy(cX,cY); cout << cuerpo;
	gotoxy(cX-1,cY-1); cout << cuerpo;
	gotoxy(cX-2,cY-2); cout << cuerpo;
	gotoxy(cX-3,cY-3); cout << cuerpo;
	gotoxy(cX+1,cY-1); cout << cuerpo;
	gotoxy(cX+2,cY-2); cout << cuerpo;
	gotoxy(cX+3,cY-3); cout << cuerpo;
	gotoxy(cX-1,cY+1); cout << cuerpo;
	gotoxy(cX-2,cY+2); cout << cuerpo;
	gotoxy(cX-3,cY+3); cout << cuerpo;
	gotoxy(cX+1,cY+1); cout << cuerpo;
	gotoxy(cX+2,cY+2); cout << cuerpo;
	gotoxy(cX+3,cY+3); cout << cuerpo;
}
class Y {
		char cuerpo = '*';
		int x;
		int y;
	public: 
		Y() {}
		void DibujarY(int cX, int cY);
		void BorrarY();
		int GetX() { return x; }
		int GetY() { return y; }
};
void Y::DibujarY(int cX, int cY) {
	setColor(color[2]);
	gotoxy(cX,cY); cout << cuerpo;
	gotoxy(cX-1,cY-1); cout << cuerpo;
	gotoxy(cX-2,cY-2); cout << cuerpo;
	gotoxy(cX-3,cY-3); cout << cuerpo;
	gotoxy(cX+1,cY-1); cout << cuerpo;
	gotoxy(cX+2,cY-2); cout << cuerpo;
	gotoxy(cX+3,cY-3); cout << cuerpo;
	gotoxy(cX,cY+1); cout << cuerpo;
	gotoxy(cX,cY+2); cout << cuerpo;
	gotoxy(cX,cY+3); cout << cuerpo;
}
bool j[9] {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,	
};
bool Comprobar1() {
	if (j[0] && j[1] && j[2]) return true;
	else if (j[3] == true && j[4] == true && j[5] == true) return true;
	else if (j[6] == true && j[7] == true && j[8] == true) return true;
	else if (j[0] == true && j[3] == true && j[6] == true) return true;
	else if (j[1] == true && j[4] == true && j[7] == true) return true;
	else if (j[2] == true && j[5] == true && j[8] == true) return true;
	else if (j[0] == true && j[4] == true && j[8] == true) return true;
	else if (j[2] == true && j[4] == true && j[6] == true) return true;
}
void BorrarMapa() {
	for (int i=0; i < 58; ++i) {
		for (int j=0; j < 150; ++j) {
			gotoxy(j,i); cout << " ";
		}
	}
}
bool j2[9] {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
};
bool Comprobar2() {
	if (j2[0] && j2[1] && j2[2]) return true;
	else if (j2[3] == true && j2[4] == true && j2[5] == true) return true;
	else if (j2[6] == true && j2[7] == true && j2[8] == true) return true;
	else if (j2[0] == true && j2[3] == true && j2[6] == true) return true;
	else if (j2[1] == true && j2[4] == true && j2[7] == true) return true;
	else if (j2[2] == true && j2[5] == true && j2[8] == true) return true;
	else if (j2[0] == true && j2[4] == true && j2[8] == true) return true;
	else if (j2[2] == true && j2[4] == true && j2[6] == true) return true;
}
int main () {
	cout << "\n \n \n presiona P para seleccionar";
	AltEnter();
	OcultarCursor();
	DibujarMapa();
	Flecha f(8,9);
	setColor(color[1]);
	f.DibujarFlecha();
	X x;
	Y y;
	bool Play = true;
	while (Play) {
		while (1) { // jugador 1
			setColor(color[1]); f.DibujarFlecha();
			if (kbhit()) {
				char tecla = getch();
				if (tecla == 'p') {
					x.DibujarX(f.GetX()+10,f.GetY());
					if (f.GetX() == 8 && f.GetY() == 9) {
						j[0] = true;
					}
					if (f.GetX() == 8 && f.GetY() == 29) {
						j[3] = true;
					}
					if (f.GetX() == 8 && f.GetY() == 49) {
						j[6] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 9) {
						j[1] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 29) {
						j[4] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 49) {
						j[7] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 9) {
						j[2] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 29) {
						j[5] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 49) {
						j[8] = true;
					}
					if (Comprobar1()) {
						BorrarMapa();
						gotoxy(80,15); cout << "Ha ganado jugador 1.";
						for (int i=0; i < 30; ++i) cout << endl;
						system("PAUSE");
						return 0;
					}
					break;
				}
				else f.MoverFlecha(tecla);
			}
		} // fin turno jugador 1
		while (1) { // jugador 2
			setColor(color[2]);
			f.DibujarFlecha();
			if (kbhit()) {
				char tecla = getch();
				if (tecla == 'p') {
					y.DibujarY(f.GetX()+10,f.GetY());
					if (f.GetX() == 8 && f.GetY() == 9) {
						j2[0] = true;
					}
					if (f.GetX() == 8 && f.GetY() == 29) {
						j2[3] = true;
					}
					if (f.GetX() == 8 && f.GetY() == 49) {
						j2[6] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 9) {
						j2[1] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 29) {
						j2[4] = true;
					}
					if (f.GetX() == 48 && f.GetY() == 49) {
						j2[7] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 9) {
						j2[2] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 29) {
						j2[5] = true;
					}
					if (f.GetX() == 88 && f.GetY() == 49) {
						j2[8] = true;
					}
					if (Comprobar2()) {
						BorrarMapa();
						gotoxy(80,15); cout << "Ha ganado jugador 2.";
						for (int i=0; i < 30; ++i) cout << endl;
						system("PAUSE");
						return 0;
					}
					break;
				}
				else f.MoverFlecha(tecla);
			} // fin if kbhit
		} // turno jugador 2
	} // while play
}