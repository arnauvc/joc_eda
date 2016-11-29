#include "Player.hh"
#include <list>
#include <map>
#include <math.h>

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
		Dir ini;
		Dir dir; // Direccio de la qual prove. Si es Node 1 -> Node 2 , el Node2 te dir Dreta
	};

	bool pos_valida(Pos p){
		Cell cela = cell(p);
		if( cela.haunted  or cela.id != -1 or cela.type == Wall) return false;
		return true;
	}
	Dir calcular_seg_dir(int d){
		int enu = (d+2)%8  ;
		return Dir(enu);
	}

	Dir calcular_seg_dir_modul8(int d){
		int enu = (d+1)%8  ;
		return Dir(enu);
	}

	int distMan(Pos a, Pos b){
		return sqrt(pow((a.i - b.i),2) + pow((a.j - b.j),2));
	}

	Dir bfs(int id){ 
		Unit unitat = unit(id);
		bool primer  = true;
		queue<Pos_Dir> Q;
		list<Dir> L;
		map<Pos, bool> visitats;
		bool pos_basica = true;
		Pos_Dir pd;
		int ran = 2*random(0,3);
		int ranK = random(0,7); // %8
		cout << "Valor inicial de busqueda:  " <<calcular_seg_dir_modul8( ranK)<< endl;
		pd.pos  = unitat.pos;
		pd.dir = Left;
		cout << "Valor de PD:  " <<pd.pos <<"   " <<pd.dir<< endl;
		auto it = visitats.find(pd.pos);
		if(it == visitats.end() ){
 			visitats[pd.pos] = false;
 		}
 		it = visitats.find(pd.pos);
 		if( (*it).second == false ){
 			if ((cell(pd.pos)).type != Wall  ){
 				Q.push(pd);
 				(*it).second = true;
 				while(not Q.empty()){
 					Pos_Dir pdNew;
					pdNew = Q.front(); 
					Q.pop();

					if(unitat.type == Farmer){
						
						if(pdNew.pos != pd.pos and not primer){
							cout << "Dins" << endl;
							cout << "Actualitzacio valor " << pdNew.pos << "    " << pdNew.dir<<endl;
							Cell cela = cell(pdNew.pos);
							cout << "Comprovacio   valor cela:    "  << cela.haunted << " Cela id:   " <<  cela.id<<endl;
							cout << "Valor de pos_basica: " << pos_basica << endl;
						
								cout << "Valor de pdNew.dir:  " << pdNew.dir << endl;
								L.push_back(pdNew.dir);
								if(cela.owner != 0 ){
									cout << "Valor de pdNew.pos:  " << pdNew.pos << "   dir:   " << pdNew.dir<< "  Ini:  " << pdNew.ini << endl;
									cout << endl;
									/*
									if( distMan(pdNew.pos, pd.pos ) == 1){
										return pdNew.dir;
									}
									list<Dir>::iterator itL;
									for(itL = L.begin(); itL != L.end(); ++itL){
										cout << "Direccions llista:  " << *itL << endl;
									}
									cout<< "Command realitzat:  " << *itL << endl;
									cout << endl;
									itL = L.begin();
									return *itL;
									*/
									return pdNew.ini;
								}
							
						}
						primer = false;
						for( int k = 0; k < 4; ++k){
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ calcular_seg_dir( ran + 2*k);
							pdSeguent.dir = calcular_seg_dir(ran + 2*k ); 
							cout << "Valor del pdNew.dir per Ini:     " << pdNew.dir << endl;
							if(pos_basica) {pdSeguent.ini = pdSeguent.dir;}
							else {pdSeguent.ini = pdNew.dir;}
							
							
							cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<<  "   Ini:   " << pdSeguent.ini << endl;
							auto it2 = visitats.find(pdSeguent.pos);
							if(it2 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it2 = visitats.find(pdSeguent.pos);
							if((*it2).second == false){
								if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted ) and (  cell(pdSeguent.pos).id == -1) ) {
									Q.push(pdSeguent);
									(*it2).second = true;
								}
							}
						}
						pos_basica = false;
					}
					else if (unitat.type == Knight){
						cout << "Es un caballeeer" << endl;
						if(pdNew.pos != pd.pos and not primer){
							cout << "Dins" << endl;
							cout << "Actualitzacio valor " << pdNew.pos << "    " << pdNew.dir<<endl;
							Cell cela = cell(pdNew.pos);
							cout << "Comprovacio   valor cela:    "  << cela.haunted << " Cela id:   " <<  cela.id<<endl;
							
								cout << "Valor de pdNew.dir:  " << pdNew.dir << endl;
								L.push_back(pdNew.dir);
								if(cela.id != -1){								
									Unit u = unit(cela.id);
									if(u.type != 2 and u.player != 0   ){
										if(distMan(pdNew.pos, pd.pos ) < 2){
											cout<< "Command Return Direccio Caballer:  " << pdNew.dir << endl;
											return pdNew.dir;
										}
										list<Dir>::iterator itL;
										for(itL = L.begin(); itL != L.end(); ++itL){
											cout << "Direccions llista:  " << *itL << endl;
										}
										cout<< "Command Direccio Caballer:  " << *(itL) << endl;
										cout << endl;
										itL = L.begin();
										return *itL;
									}
								}
								
						}
						primer = false;
						for(int k = 0; k < 8; ++k){
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ calcular_seg_dir_modul8( ranK + k);
							pdSeguent.dir = calcular_seg_dir_modul8(ranK + k); 
							
							cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<< endl;
							auto it3 = visitats.find(pdSeguent.pos);
							if(it3 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it3 = visitats.find(pdSeguent.pos);
							if((*it3).second == false){
								if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted ) ) {
									Q.push(pdSeguent);
									(*it3).second = true;
								}
							}
						}
						
					}
 				}
 			}
 		}
		cout <<"What da hell is happening" << endl;
		return Right;
	}
  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		VE f = farmers(0);
		VE k = knights(0);
		VE w = witches(0);
		//int id = 14; 
		
		
		for (unsigned int i = 0 ; i <  f.size(); ++i) {
			 cout << "Ronda num: " << round()<< endl;
			command(f[i] ,bfs(f[i])); 
		}
		
		
		if( round() < 200){
			cout << "Ronda num: " << round()<< endl;
			
			for (unsigned int j= 0 ; j < k.size(); ++j) {
				cout << "ID Cavaller: " << k[j] << endl;
				command(k[j], bfs(k[j]));
			}

		}
		

		
		if (round() < 40) command(w[0], Right);
		    else if (round() < 80) command(w[0], Bottom);
		    else if (round() < 120) command(w[0], Top);
		    else if (round() < 160) command(w[0], Bottom);
		    else {
		      set<Pos> s;
		      while ((int)s.size() < 4) s.insert(Pos(random(0, 36), random(0, 36)));
		      vector<Pos> v(s.begin(), s.end());
		      if (v[random(0, 3)].i < 18) command(w[0], None);
		      else command(w[0], Top);
		    }
		if (round() < 40) command(w[1], Bottom);
		    else if (round() < 80) command(w[1], Right);
		    else if (round() < 120) command(w[1], Left);
		    else if (round() < 160) command(w[1], Right);
		    else {
		      set<Pos> s;
		      while ((int)s.size() < 4) s.insert(Pos(random(0, 36), random(0, 36)));
		      vector<Pos> v(s.begin(), s.end());
		      if (v[random(0, 3)].i < 18) command(w[1], None);
		      else command(w[1], Top);

    		}
    		

		

  	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
