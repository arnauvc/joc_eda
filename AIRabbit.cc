#include "Player.hh"
#include <list>
#include <map>


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
	struct Pos_Dir {
		Pos pos;
		Dir dir; // Direccio de la qual prove. Si es Node 1 -> Node 2 , el Node2 te dir Dreta
	};

	Dir bfs(int id){
		Unit farmer = unit(id);	
		//Structures
		queue<Pos_Dir> Q;
		list<Pos_Dir> L;
		map<Pos, bool> visitats;
		//MAT enc(37,vector<int>(37,0));

		for(int i = 0 ; i < 4 ; ++i ){
			Pos_Dir pd;
			pd.pos  = farmer.pos;
			if(i == 0) {pd.pos = pd.pos + Right; pd.dir = Right;}
			else if (i == 1){pd.pos= pd.pos + Bottom; pd.dir = Bottom;}
			else if (i == 2){pd.pos = pd.pos + Left; pd.dir = Left;}
			else {pd.pos = pd.pos + Top; pd.dir = Top;}

			auto it = visitats.find(pd.pos);
			if( (cell(pd.pos).type != Wall ) and (it != visitats.end() and (*it).second == false) ){
				Q.push(pd);
				(*it).second = true;
				while(not Q.empty()){
					Pos_Dir pdNew;
					pdNew = Q.front(); 
					Q.pop();
					//////Evaluar si la cella es bona per mouresi
					Cell cela = cell(pdNew.pos);
					if(cela.owner != 0 and not cela.haunted and cela.id == -1)
						return pdNew.dir;
					/////
					for(int k = 0; k < 4; ++k){
						Pos_Dir pdSeguent;
						if(k == 0) {pdSeguent.pos = pdNew.pos+ Right; pdSeguent.dir = Right;}
						else if (k == 1){pdSeguent.pos = pdNew.pos + Bottom; pdSeguent.dir = Bottom;}
						else if (k == 2){pdSeguent.pos = pdNew.pos + Left; pdSeguent.dir = Left;}
						else {pdSeguent.pos = pdNew.pos + Top; pdSeguent.dir = Top;}
						auto it2 = visitats.find(pdSeguent.pos);
						if(  (cell(pdSeguent.pos).type != Wall) and (it2 != visitats.end() and (*it2).second == false) ){//not enc[pdSeguent.pos.i, pdSeguent.pos.j]){
							Q.push(pdSeguent);
							(*it2).second = true;
							//enc[pdSeguent.pos.i, pdSeguent.pos.j] = true;
						}
					}
				}
			}
		}

	return None;
	}
  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		VE f = farmers(0);
		VE k = knights(0);
		VE w = witches(0);

		for(int id : f){
			command(id, bfs(id));
		}

  	}

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
