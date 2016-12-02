#include "Player.hh"
#include <list>
#include <map>
#include <math.h>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Hamster


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
        		Pos posP;
		Dir ini;
		Dir dir; // Direccio de la qual prove. Si es Node 1 -> Node 2 , el Node2 te dir Dreta
		bool inicial;
	};

	struct BT{
	    	bool b = true;
	    	UnitType ut;
	    };

     	vector<Dir> vdir{Top,RT,Right, BR,Bottom,LB,Left, TL};

	Dir calcular_seg_dir(int d){
		int enu = (d+2)%8  ;
		return Dir(enu);
	}

	Dir calcular_seg_dir_modul8(int d){
		int enu = (d+1)%8  ;
		return Dir(enu);
	}

	void emplenar_cell_segura(vector< vector<BT> > & cell_segura){
		for(int m = 1; m < 37; ++m){
			for(int n = 1; n < 37; ++n){
				Cell c = cell(m,n);
				if(c.type != Wall){
					if(c.id != -1){
				                	Unit u = unit(c.id);
					            int i = (u.pos).i;
					            int j = (u.pos).j;
					            if((unit(c.id).player != 0) and (unit(c.id).type == 1)){
					            	cell_segura[i][j].b = false;
							cell_segura[i][j].ut = Knight;
					                	for(int k = 0; k< 8; ++k){
					                            	Pos p(m,n);
					                            	p += vdir[k];
						                        if(cell(p).type != Wall) {
							                        cell_segura[p.i][p.j].b = false;
							                        cell_segura[p.i][p.j].ut = Knight;
						                        }
					                        }
					            }
					            else if((cell_segura[m][n].b) and (unit(c.id).type == 2)){
					                 	cell_segura[i][j].b = false;
							cell_segura[i][j].ut = Witch;
					            }
				                }
				                else if (c.haunted){
				                	cell_segura[m][n].b = false;
						cell_segura[m][n].ut = Witch;
				                    	for(int l = 0; l<8 ; l+=2){
				                      		Pos pt(m,n);
				                      		pt += vdir[l];
					                       	if(cell(pt).type != Wall ) {
						                	cell_segura[pt.i][pt.j].b = false;
						                        cell_segura[pt.i][pt.j].ut = Witch;
						            }
				                    	}
				            }
				}
				else cell_segura[m][n].b = false;
			 }
		}
	}

    Dir bfs(int id, vector< vector<BT> > & cell_segura, vector<vector<bool> >& proper_moviment){
		Unit unitat = unit(id);
		bool primer = true;
		queue<Pos_Dir> Q;
		map<Pos, bool> visitats;
		Pos_Dir pd;
		int ran = 2*random(0,3);
		int ranK = random(0,7); // %8
		vector<Dir> seg_dir (4);
		vector<Dir> seg_dir8 (8);
		for(int a = 0; a < 4; ++a){
			seg_dir[a] = calcular_seg_dir( ran + 2*a);
		}
		for(int b = 0; b < 8; ++b){
			seg_dir8[b] = calcular_seg_dir_modul8( ranK + b);
		}
		pd.pos  = unitat.pos;
		pd.dir = Left;


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
							//cout << "Dins" << endl;
							//cout << "Actualitzacio valor. Pos:  " << pdNew.pos << "  Dir:  " << pdNew.dir << " Ini: "<<  pdNew.ini<<endl;
							Cell cela = cell(pdNew.pos);
							//cout << "Comprovacio   valor cela:    "  << cela.haunted << " Cela id:   " <<  cela.id<<endl;
							//cout << "Valor de pdNew.dir:  " << pdNew.dir << endl;
	                           					if(cela.owner != 0 and proper_moviment[pdNew.posP.i][pdNew.posP.j]){
	                               		 			//cout << "Comanda a executa. Pos:  " << pdNew.pos << "   dir:   " << pdNew.dir<< "  Ini:  " << pdNew.ini << endl;
									cout << endl;
	                                 					proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;
									return pdNew.ini;
								}
						}
						for( int k = 0; k < 4; ++k){
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ seg_dir[k];
							pdSeguent.dir = seg_dir[k]; 
							//cout << "Direccio de pdSeguent Farmer:  " << seg_dir[k]<< endl;
							if(primer)pdSeguent.inicial = true;
							else pdSeguent.inicial = false;
						                            if(pdSeguent.inicial) {
						                                pdSeguent.ini = pdSeguent.dir;
						                                pdSeguent.posP = pdSeguent.pos;
						                            }
						                            else {
						                                pdSeguent.ini = pdNew.ini;
						                                pdSeguent.posP = pdNew.posP;
						                            }
							
							//cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<<  "   Ini:   " << pdSeguent.ini << endl;
							auto it2 = visitats.find(pdSeguent.pos);
							if(it2 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it2 = visitats.find(pdSeguent.pos);
							if((*it2).second == false){
                               						if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted ) and (  cell(pdSeguent.pos).id == -1)  and cell_segura[pdSeguent.pos.i][pdSeguent.pos.j].b) {
									Q.push(pdSeguent);
									(*it2).second = true;
								}
							}
						}
						primer = false;
					}
					else if (unitat.type == Knight){
						if(pdNew.pos != pd.pos and not primer){
							Cell cela = cell(pdNew.pos);
							if(cela.id != -1){
								Unit u = unit(cela.id);
	                                						if(u.type != 2 and u.player != 0 and proper_moviment[pdNew.posP.i][pdNew.posP.j]){
	                                     						proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;
	                                    						return pdNew.ini;
									}
							}
						}
						for( int k = 0; k < 8; ++k){
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ seg_dir8[k];
							pdSeguent.dir = seg_dir8[k]; 
							//cout << "Direccio de pdSeguent Knight:  " << seg_dir8[k]<< endl;
							if(primer)pdSeguent.inicial = true;
							else pdSeguent.inicial = false;
						                	if(pdSeguent.inicial) {
							                                pdSeguent.ini = pdSeguent.dir;
							                                pdSeguent.posP = pdSeguent.pos;
						                           	}
						                            	else {
							                                pdSeguent.ini = pdNew.ini;
							                                pdSeguent.posP = pdNew.posP;
						                          	}
							//cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<<  "   Ini:   " << pdSeguent.ini << endl;
							auto it3 = visitats.find(pdSeguent.pos);
							if(it3 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it3 = visitats.find(pdSeguent.pos);
							if((*it3).second == false){
									bool capdins = false;
									
						                               if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted )/*and  (cell_segura[pdSeguent.pos.i][pdSeguent.pos.j].b and  cell_segura[pdSeguent.pos.i][pdSeguent.pos.j].ut != Witch)*/ ) {
						                                   	// cout << "Ha carregat la cela" << pdSeguent.pos  << "Amb direccio: " << pdSeguent.dir << endl;
						                                    	Q.push(pdSeguent);
									(*it3).second = true;
								}
							}
						}
						primer = false;
					}
					else if (unitat.type == Witch){
						if(pdNew.pos != pd.pos and not primer){
							Cell cela = cell(pdNew.pos);
							if(cela.id != -1){
								Unit u = unit(cela.id);
	                                					if( u.type != 2 and  u.player != 0 and proper_moviment[pdNew.posP.i][pdNew.posP.j]){
	                                     						proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;
	                                    						return pdNew.ini;
									}
							}
						}
						for( int k = 0; k < 4; ++k){
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ seg_dir[k];
							pdSeguent.dir = seg_dir[k];
							//cout << "Valor del pdNew.dir per Ini:     " << pdNew.dir << endl;
							if(primer)pdSeguent.inicial = true;
							else pdSeguent.inicial = false;
						                	if(pdSeguent.inicial) {
							                                pdSeguent.ini = pdSeguent.dir;
							                                pdSeguent.posP = pdSeguent.pos;
						                           	}
						                            	else {
							                                pdSeguent.ini = pdNew.ini;
							                                pdSeguent.posP = pdNew.posP;
						                          	}
							//cout << "Valor de pdSeguent:  " <<pdSeguent.pos <<"   " <<pdSeguent.dir<<  "   Ini:   " << pdSeguent.ini << endl;
							auto it3 = visitats.find(pdSeguent.pos);
							if(it3 == visitats.end() ){ 
								visitats[pdSeguent.pos] = false;
							}
							it3 = visitats.find(pdSeguent.pos);
							if((*it3).second == false){
						                                if(  (cell(pdSeguent.pos).type != Wall )  /*and  (cell_segura[pdSeguent.pos.i][pdSeguent.pos.j].b and  cell_segura[pdSeguent.pos.i][pdSeguent.pos.j].ut != Witch)*/ ) {
						                                   	// cout << "Ha carregat la cela" << pdSeguent.pos  << "Amb direccio: " << pdSeguent.dir << endl;
						                                    	Q.push(pdSeguent);
										(*it3).second = true;
								}
							}
						}
						primer = false;
					}
 				}
 			}
 		}
	//cout <<"What da hell is happening" << endl;
       	 return None;
	}
  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		VE f = farmers(0);
		VE k = knights(0);
		VE w = witches(0);

	        	vector< vector<BT> > cell_segura(37, vector<BT>(37));
	       	vector<vector<bool> > proper_moviment(37, vector<bool>(37, true)); //true es pot fer moviment, false, ocupat

	       	emplenar_cell_segura(cell_segura);

		for (unsigned int i = 0 ; i <  f.size(); ++i) {
			command(f[i] ,bfs(f[i], cell_segura, proper_moviment)); 
		}
		
		for (unsigned int j= 0 ; j < k.size(); ++j) {
			command(k[j], bfs(k[j],cell_segura, proper_moviment));
		} 

		command(w[0], bfs(w[0],cell_segura, proper_moviment));

		command(w[1], bfs(w[1],cell_segura, proper_moviment));

		
  	}
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
           