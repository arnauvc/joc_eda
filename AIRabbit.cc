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

	bool pos_valida(Pos p){
		Cell cela = cell(p);
		if( cela.haunted  or cela.id != -1 or cela.type == Wall) return false;
		return true;
	}

	list<Dir> bfs(int id){
		Unit farmer = unit(id);	
		//Structures
		queue<Pos_Dir> Q;
		list<Dir> L;
		map<Pos, bool> visitats;

		for(int i = 0 ; i < 1; ++i ){
			Pos_Dir pd;
			pd.pos  = farmer.pos;
			pd.dir = None;
			auto it = visitats.find(pd.pos);
			if ((cell(pd.pos)).type != Wall  ){
				bool entrat = false;
				if(it == visitats.end() ){
 					visitats[pd.pos] = false;
 					entrat = true;
 				}
				if( (*it).second == false or entrat){
					
					Q.push(pd);
					(*it).second = true;
					while(not Q.empty()){
						Pos_Dir pdNew;
						pdNew = Q.front(); 
						Q.pop();
						//////Evaluar si la cella es bona per mouresi
						if(pdNew.pos != pd.pos){
							
							Cell cela = cell(pdNew.pos);
							if( not cela.haunted and cela.id != -1){
								
								L.push_back(pdNew.dir);	
							}
							if(cela.owner != 0 and not cela.haunted and cela.id == -1){
								
								return L;	
							}
						}
						
						for(int k = 0; k < 4; ++k){
							
							Pos_Dir pdSeguent;
							if(k == 0) {pdSeguent.pos = pdNew.pos+ Right; pdSeguent.dir = Right; }
							else if (k == 1){pdSeguent.pos = pdNew.pos + Bottom; pdSeguent.dir = Bottom;}
							else if (k == 2){pdSeguent.pos = pdNew.pos + Left; pdSeguent.dir = Left;}
							else {pdSeguent.pos = pdNew.pos + Top; pdSeguent.dir = Top;}
							auto it2 = visitats.find(pdSeguent.pos);
							
							if(  (cell(pdSeguent.pos).type != 1) ) {
								
								bool entrat2 = false;
								if(it2 == visitats.end() ){ 
									visitats[pdSeguent.pos] = false;
									entrat2 = true;
								}
								if((*it2).second == false or entrat2){
									Q.push(pdSeguent);
									(*it2).second = true;
								
								}
							}
						}
					}
				}	
			}
		}
	cerr << None << endl;
	return L;
	}
  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		VE f = farmers(0);
		VE k = knights(0);
		VE w = witches(0);
		//int id = 14;
		for (unsigned int i = 0 ; i < f.size(); ++i) {
			if((round() < 4 ) or (round() > 25 and round() < 31) or (round() > 63 and round() < 68) or (round() >127 and round() < 133)){
				cerr << round() << endl; //////////////// round
				Dir d = Dir(2*random(0, 3));
				while(not (pos_valida(unit(f[i]).pos +  d))  ) {
					d = Dir(2*random(0, 3));
				}
				command(f[i], d );
			}
			else{
			
			
			list<Dir> L= bfs(f[i]);
			list<Dir>::iterator it = L.begin();
			command(f[i], *it); 
			}
		}
		for (unsigned int j= 0 ; j < k.size(); ++j) {
			
			list<Dir> L= bfs(k[j]);
			list<Dir>::iterator it = L.begin();
			command(k[j], *it);
			
		}
		for (int i : f) {}

  	}

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
