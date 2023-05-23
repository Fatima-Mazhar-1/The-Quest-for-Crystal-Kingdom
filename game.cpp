#include<iostream>
#include"graph.h"
#include"avlTreeh.h"
#include <windows.h>

using namespace std;


typedef enum {
	black,
	blue,
	green,
	cyan,
	red,
	magenta,
	yellow,
	white,
	gray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightmagenta,
	lightyellow,
	lightwhite
};//colors
void setColor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}//to set colors

class Game {
	AVLNode* root;
	AVLTree tree;
public:
	Game() {
		root = nullptr;
	}
	void insertinAvl(char c) {
		if (root == nullptr) {
			root = tree.insert(root, 100, c);
		}
		else {
			int id = rand() % 201;
			bool falg = false;
			AVLNode* zed = tree.search(root, id);
			if (zed != nullptr)
				if (zed->type == c) {
					zed->count++;
					falg = true;
					zed->score = zed->score * zed->count;

				}
				else {
					while (zed == nullptr) {
						zed = tree.search(root, id);
						if (zed != nullptr)
							if (zed->type == c) {
								zed->count++;

								falg = true;
								zed->score = zed->score * zed->count;
								break;
							}
					}
				}
			if (falg != true)
				root =tree.insert(root, id, c);
		}
	}
	void playGame(Map map, int size) {
		char input;
		map.PrintMap();
		cout << "Please enter the direction ";
		cin >> input;
		Beep(500, 1000);
		bool flag = true;
		bool lol = false;
		for (int i = 0; i < size;) {
			for (int j = 0; j < size;) {
				flag = true;
				if (input == 'u')
				{
					if (i > 0) {
						i = i - 1;
						flag = false;
					}
					else {

						cout << "Cannot go there " << endl;
						Sleep(90);
						Beep(500, 1000);
					}
				}
				if (input == 'd') {
					if (i < size - 1) {
						i = i + 1;
						flag = false;
					}
					else {

						cout << "Cannot go there " << endl;
						Sleep(90);
						Beep(500, 1000);
					}
				}
				if (input == 'r') {
					if (j < size - 1) {
						j++;
						flag = false;
					}
					else {

						cout << "cannot go there " << endl;
						Sleep(90);
						Beep(500, 1000);
					}
				}
				if (input == 'l') {
					if (j > 0) {
						j--;
						flag = false;
					}
					else {

						cout << "Cannot go there " << endl;
						Sleep(90);
						Beep(500, 1000);
					}
				}
				if (!flag) {
					insertinAvl(map.getCharAtindex(i, j));
				}
				system("CLS");
				map.PrintMap();
				cout << "Please enter direction ";
				cin >> input;
				Beep(500, 1000);
				if (input == 'z') {
					lol = true;
					break;
				}
			}
			if (lol)
				break;
		}
		cout << "Your score is " <<tree.countIds(root) << endl;
	}
};
int main() {
	setColor(red, black);
	cout << "-_-_-_-_-_-_-_-_-_-_-_-_THE QUEST FOR THE CRYSTAL KINGDOM-_-_-_-_-_-_-_-_-_-_-_-_\n" <<endl;
	setColor(white, black);
	srand(time(NULL));
	Map map(10);
	map.GenerateMap();
	//map.PrintMap();
	Graph<int> graph(100);
	graph.convertToMatrix(map, 10, 10);
	//graph.PrintMatrix();
	int count = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map.getCharAtindex(i, j) == '*') {
				setColor(magenta, black);
				cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-Dijkstra result-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
				setColor(white, black);
				dijkstra(graph.Matrix, graph.Vertices, count,0);
				setColor(magenta, black);
				cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-Floyd result -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
				setColor(white, black);
				floyd(graph.Matrix, graph.Vertices, count,0);
			}
			count++;
		}
	}


	prim(graph.Vertices, graph.Matrix);
	kruskal(graph.Vertices, graph.Matrix);
	cout << endl;
	setColor(magenta, black);
	cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-Play The Game-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
	setColor(white, black);
	Game game;
	game.playGame(map, 10);

}