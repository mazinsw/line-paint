#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include "classes/glwindow.h"
#include "linha.h"
#include <list>

const float cores[10][3] =
{
	{ 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.5f, 0.2f },
	{ 0.5f, 0.5f, 0.5f },
	{ 0.1f, 0.4f, 0.8f },
	{ 0.0f, 0.0f, 0.0f }
};

class LinePaint: public GLWindowBase
{
private:
	std::list<Linha*> linhas;
	/* ultima coordenada que foi clicada */
	Coordenada ult_coord;
	/* quantidade de pontos já definidos */
	int qtd_coord;
	/* cor da próxima linha */
	float r_fg, g_fg, b_fg;
	/* cor do fundo */
	float r_bg, g_bg, b_bg;
	/* posição do mouse */
	int x, y;
protected:
	/**
	 * Limpa todas as linhas
	 */
	void limpar()
	{
		std::list<Linha*>::iterator it;
		// como as linhas são ponteiros é necessário destruí-las primeiro
		for(it = linhas.begin(); it != linhas.end(); it++)
			delete *it;
		linhas.clear();
	}

	/**
	 * desenha no plano 2D
	 */
	virtual void onCreate()
	{
		resize2DScene();
	}

	/**
	 * Obtem as coordenadas do clique do mouse para formar as linhas
	 */
	virtual void onMouseDown(int x, int y, int button, int state)
	{
		Linha* linha;

		if(button == SDL_BUTTON_LEFT)
		{
			qtd_coord++;
			// já formou 2 pontos
			if(qtd_coord > 1)
			{
				linha = new Linha(ult_coord.getX(), ult_coord.getY(), x, y,
								  r_fg, g_fg, b_fg);
				linhas.push_back(linha);
			}
			ult_coord.setX(x);
			ult_coord.setY(y);
		}
	}

	/**
	 * atualiza a posição do mouse
	 */
	virtual void onMouseMove(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		int cor;
		Linha* linha;

		// o primeiro ESC cancela o desenho da linha
		if(key == SDLK_ESCAPE)
		{
			if(qtd_coord > 0)
				qtd_coord = 0;
			else
				close();
		}
		// limpa a tela
		else if(key == SDLK_DELETE)
		{
			limpar();
			qtd_coord = 0;
		}
		// teclas de 0 até 9 para controle das cores
		else if((key >= SDLK_0 && key <= SDLK_9) || (key >= SDLK_KP0 && key <= SDLK_KP9))
		{
			// transforma de 0 à 9
			if(key >= SDLK_KP0)
				cor = key - SDLK_KP0;
			else
				cor = key - SDLK_0;
			// alterando a cor da linha
			if((state & LeftCtrl) == 0)
			{
				r_fg = cores[cor][0];
				g_fg = cores[cor][1];
				b_fg = cores[cor][2];
			}
			else // alterando a cor do fundo com o Ctrl pressionado
			{
				r_bg = cores[cor][0];
				g_bg = cores[cor][1];
				b_bg = cores[cor][2];
			}
		}
		// apaga os pontos da linha com o backspace
		else if(key == SDLK_BACKSPACE)
		{
			if(qtd_coord > 1 && linhas.size() > 0)
			{
				qtd_coord--;
				linha = linhas.back();
				// a coordenada no ultimo ponto volta a ser a do penúltimo ponto
				ult_coord.setX(linha->getP1().getX());
				ult_coord.setY(linha->getP1().getY());
				delete linha;
				linhas.pop_back();
			}
		}
		else  // o outro ESC fecha a janela
			GLWindowBase::onKeyDown(key, state);
	}

	/**
	 * desenha as linhas
	 */
	virtual void render()
	{
		std::list<Linha*>::iterator it;
		Linha* linha;

		// limpa o buffer
		glClearColor( r_bg, g_bg, b_bg, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// percorre todas as linhas e desenha uma por uma
		for(it = linhas.begin(); it != linhas.end(); it++)
		{
			linha = *it;
			linha->render();
		}
		// desenha uma linha para sabermos o início e fim da mesma
		if(qtd_coord > 0)
		{
			glBegin( GL_LINES );
			glColor3f( r_fg, g_fg, b_fg );
			glVertex2i( ult_coord.getX(), ult_coord.getY() );
			glVertex2i( x, y );
			glEnd();
		}
		// mostra as linhas
		swapBuffers();
	}
public:
	LinePaint()
	{
		qtd_coord = 0;
		r_fg = g_fg = b_fg = 1.0f; // inicializa a cor da linha com branco
		r_bg = g_bg = b_bg = 0.0f; // inicializa a cor de fundo com preto
	}

	~LinePaint()
	{
		// antes de destruir a janela destroi as linhas
		limpar();
	}
};

int main(int argc, char *argv[])
{
	LinePaint lp;

	lp.setTitle("LinePaint");
	return lp.start(argc, argv);
}

