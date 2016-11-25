#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Rabbit


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
	typedef vector<int> VE;
	typedef vector< vector<int>> MAT;
	
	int dis_Man(Pos A, Pos B){
	
		return 0;
	}

  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		VE f = farmers(0);
		VE k = knights(0);
		VE w = witches(0);
		for(int id : f){

			Unit farmer = unit(id);
			queue<Pos> Q;

			//possible mapa o set de pos: unordered_map(Pos, bool)
			MAT enc(20,vector<int>(20),false);
			
			for(int i = 0 ; i < 4 ; ++i ){
					Pos p = Pos(0,i);
				if(cell(p).type != Wall && not enc[p.i, p.j]){
					Q.push(p);
					while(not Q.empty()){
						Pos posicio = Q.front(); Q.pop();
						//////Evaluar si la cella es bona per mouresi
						Cell cela = cell(posicio);
						if(cela.owner != 0 and not cela.haunted and cela.id == -1)
							command(id, Dir(random(0, 7)));
						/////
						for(int k = 0; k < 4; ++k){
							Pos posicioNew;
							if(k == 0) posicioNew = posicio + Top;
							else if (k == 1)posicioNew = posicio + Right;
							else if (k == 2)posicioNew = posicio + Bottom;
							else posicioNew = posicio + Left;
							if(cell(posicioNew).type != Wall and not enc[posicioNew.i, posicioNew.j]){
								Q.push(posicioNew);
								enc[posicioNew.i, posicioNew.j] = true;
							}
						}
							

					}
				}
			}


			//command(id, Dir(random(0, 7)));
		}

  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
