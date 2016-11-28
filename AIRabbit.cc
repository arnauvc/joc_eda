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
		Dir dir; // Direccio de la qual prove. Si es Node 1 -> Node 2 , el Node2 te dir Dreta
	};

	bool pos_valida(Pos p){
		Cell cela = cell(p);
		if( cela.haunted  or cela.id != -1 or cela.type == Wall) return false;
		return true;
	}
	Dir calcular_seg_dir(int d){
		int enu = (d+2)%8  ;
		if ( enu == 0 )return Bottom;
		else if (enu == 2)return Right;
		else if (enu == 4)return Top;
		else if (enu == 6) return Left;
		else return None;
	}

	Dir calcular_seg_dir_modul8(int d){
		int enu = (d+1)%8  ;
		if ( enu == 0 )return Bottom;
		else if (enu == 1)return BR;
		else if (enu == 2)return Right;
		else if (enu == 3) return RT;
		else if (enu == 4)return Top;
		else if (enu == 5)return TL;
		else if (enu == 6) return Left;
		else if (enu == 7) return LB;
		else return None;
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
							if( not cela.haunted and cela.id == -1){
								cout << "Valor de pdNew.dir:  " << pdNew.dir << endl;
								L.push_back(pdNew.dir);
								if(cela.owner != 0 ){
									if( distMan(pdNew.pos, pd.pos ) == 1){
										return pdNew.dir;
									}
									list<Dir>::iterator itL;
									for(itL = L.begin(); itL != L.end(); ++itL){
										cout << "Direccions llista:  " << *itL << endl;
									}
									if(round() < 3) cout<< "Command realitzat:  " << *itL << endl;
									cout << endl;
									itL = L.begin();
									return *itL;
								}
							}	
						}
						primer = false;
						for(int k = 0; k < 4; ++k){
							Pos_Dir pdSeguent;
							if(k == 0) {
								pdSeguent.pos = pdNew.pos+ calcular_seg_dir( ran);
								pdSeguent.dir = calcular_seg_dir(ran ); 
							}
							else if (k == 1){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir(ran +2); 
								pdSeguent.dir = calcular_seg_dir(ran +2);
							}
							else if (k == 2){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir(ran +4 ); 
								pdSeguent.dir = calcular_seg_dir(ran +4 );
							}
							else {
								pdSeguent.pos = pdNew.pos + calcular_seg_dir(ran +6); 
								pdSeguent.dir = calcular_seg_dir(ran +6 );
							}
							cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<< endl;
							auto it2 = visitats.find(pdSeguent.pos);
							if(it2 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it2 = visitats.find(pdSeguent.pos);
							if((*it2).second == false){
								if(  (cell(pdSeguent.pos).type != Wall) ) {
									Q.push(pdSeguent);
									(*it2).second = true;
								}
							}
						}
					}
					else if (unitat.type == Knight){
						cout << "Es un caballeeer" << endl;
						if(pdNew.pos != pd.pos and not primer){
							cout << "Dins" << endl;
							cout << "Actualitzacio valor " << pdNew.pos << "    " << pdNew.dir<<endl;
							Cell cela = cell(pdNew.pos);
							cout << "Comprovacio   valor cela:    "  << cela.haunted << " Cela id:   " <<  cela.id<<endl;
							if( not cela.haunted ){
								cout << "Valor de pdNew.dir:  " << pdNew.dir << endl;
								L.push_back(pdNew.dir);
								Unit u = unit(cela.id);

								if(u.type != 2 and u.player != 0   ){
									if( distMan(pdNew.pos, pd.pos ) <= 1){
										cout<< "Command Return Direccio Caballer:  " << pdNew.dir << endl;
										return pdNew.dir;
									}
									list<Dir>::iterator itL;
									for(itL = L.begin(); itL != L.end(); ++itL){
										cout << "Direccions llista:  " << *itL << endl;
									}
									cout<< "Command Direccio Caballer:  " << *itL << endl;
									cout << endl;
									itL = L.begin();
									return *itL;
								}
							}	
						}
						primer = false;
						for(int k = 0; k < 8; ++k){
							Pos_Dir pdSeguent;
							if(k == 0) {
								pdSeguent.pos = pdNew.pos+ calcular_seg_dir_modul8( ranK);
								pdSeguent.dir = calcular_seg_dir_modul8(ranK ); 
							}
							else if (k == 1){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +1); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +1);
							}
							else if (k == 2){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +2 ); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +2 );
							}
							else if (k == 3){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +3); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +3);
							}
							else if (k == 4){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +4 ); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +4 );
							}
							else if (k == 5){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +5); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +5);
							}
							else if (k == 6){
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +6); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +6 );
							}
							else {
								pdSeguent.pos = pdNew.pos + calcular_seg_dir_modul8(ranK +7 ); 
								pdSeguent.dir = calcular_seg_dir_modul8(ranK +7);
							}
							
							cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<< endl;
							auto it3 = visitats.find(pdSeguent.pos);
							if(it3 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it3 = visitats.find(pdSeguent.pos);
							if((*it3).second == false){
								if(  (cell(pdSeguent.pos).type != Wall) ) {
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
		
		/*
		for (unsigned int i = 0 ; i < f.size(); ++i) {
			if(round() < 3) cout << "Ronda num: " << round()<< endl;
			command(f[i] ,bfs(f[i])); 
		}
		*/
		if( round() < 200 ){
			cout << "Ronda num: " << round()<< endl;
			for (unsigned int j= 0 ; j < k.size(); ++j) {
				command(k[j], bfs(k[j]));
			}
		}
		/*
		for (int i : f) {

		}
		*/
  	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
