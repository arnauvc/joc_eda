#include "Player.hh"
#include <list>
#include <map>
#include <math.h>

#define PLAYER_NAME Otter2

struct PLAYER_NAME : public Player {

	static Player* factory () {
		return new PLAYER_NAME;
	}

	typedef vector<int> VE;
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

	void emplenar_cell_segura(vector< vector<BT> > & cell_segura){
		for(int m = 1; m < 37; ++m){
			for(int n = 1; n < 37; ++n){
				Cell c = cell(m,n);
				if(c.type != Wall){
					if(c.id != -1){
				                	Unit u = unit(c.id);
					            	int i = (u.pos).i;
					            	int j = (u.pos).j;
					            	if((u.player != 0) and (u.type == 1)){
					            		cell_segura[i][j].b = false;
							cell_segura[i][j].ut = Knight;
					                	for(int k = 0; k< 8; ++k){
					                            	Pos p(m,n);
					                            	p += vdir[k];
						                        	if(cell(p).type != Wall) {
							                	cell_segura[p.i][p.j].b = false;
							                        	cell_segura[p.i][p.j].ut = Knight;
						                        	}
						                        	cell_segura[p.i][p.j].b = false;
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
						            	else  cell_segura[pt.i][pt.j].b = false;
				                    	}
				            	}
				}
				else cell_segura[m][n].b = false;
			 }
		}
	}

   	Dir bfs(int id,vector< vector<BT> >& cell_segura ,vector<vector<bool> > & proper_moviment){
		queue<Pos_Dir> Q;
		vector < vector<bool> > enc (37, vector<bool>(37, false));
		int ran = 2*random(0,3);
		int cell_sense_id = 0;
		Pos_Dir pd;
		pd.pos = unit(id).pos;
		pd.dir = None;
		pd.ini = None;
 		Q.push(pd);
 		enc[pd.pos.i][pd.pos.j] = true;
 		while(not Q.empty()){
 			Pos_Dir pdNew = Q.front(); 
			Q.pop();
			if(unit(id).type == Farmer){
				if(pdNew.dir != None){
					Cell cela = cell(pdNew.pos);
	                           			if(cela.owner != 0   and  proper_moviment[pdNew.posP.i][pdNew.posP.j] ){   
	                         				proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;
						return pdNew.ini;
					}
				}
				for( int k = 0; k < 4; ++k){
					ran = (2+ran)%8;
					Pos_Dir pdSeguent;
					pdSeguent.pos = pdNew.pos+ vdir[ran];
					pdSeguent.dir = vdir[ran]; 
				              if(pdNew.dir == None) {
				                	pdSeguent.ini = pdSeguent.dir;
				                	pdSeguent.posP = pdSeguent.pos;
				              }
				              else {
				              	pdSeguent.ini = pdNew.ini;
				              	pdSeguent.posP = pdNew.posP;
				              }
					if(not enc[pdSeguent.pos.i][pdSeguent.pos.j] ){
                               				if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted ) and (cell(pdSeguent.pos).id == -1) and  (cell_segura[pdSeguent.posP.i][pdSeguent.posP.j].b)) {
							Q.push(pdSeguent);
							enc[pdSeguent.pos.i][pdSeguent.pos.j] = true;
						}
					}
				}
			}
			else if(unit(id).type == Knight){
				if(pdNew.dir != None){
					Cell cela = cell(pdNew.pos);
	                           			if(cela.id != -1  ){
	                           				Unit u = unit(cela.id);
	                           				if(u.type != 2 and u.player != 0  and  proper_moviment[pdNew.posP.i][pdNew.posP.j] ){
	                           						proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;

									return pdNew.ini;
	                           						}  
	                           						else if ( u.player == 0  and u.type != 2){
									if ((unit(id)).health <= 90){
										++cell_sense_id;
										if (cell_sense_id >= 7) return None;
									}	
								}	
							}
							else {
								if ((unit(id)).health <= 90){
									++cell_sense_id;
									if (cell_sense_id >= 7) return None;
								}
							}
						}
						for( int k = 0; k < 8; ++k){
							ran = (1+ran)%8;
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ vdir[ran];
							pdSeguent.dir = vdir[ran]; 
						              if(pdNew.dir == None) {
						                	pdSeguent.ini = pdSeguent.dir;
						                	pdSeguent.posP = pdSeguent.pos;
						              }
						              else {
						             		pdSeguent.ini = pdNew.ini;
						              	pdSeguent.posP = pdNew.posP;
						              }
							if(not enc[pdSeguent.pos.i][pdSeguent.pos.j] ){
                               						if(  (cell(pdSeguent.pos).type != Wall) and (not cell(pdSeguent.pos).haunted )   and ( (cell_segura[pdSeguent.posP.i][pdSeguent.posP.j].b) or  ((not cell_segura[pdSeguent.posP.i][pdSeguent.posP.j].b) and cell_segura[pdSeguent.posP.i][pdSeguent.posP.j].ut != Witch))  ) {
									Q.push(pdSeguent);
									enc[pdSeguent.pos.i][pdSeguent.pos.j] = true;
								}
							}
						}
					}
					else if(unit(id).type == Witch){
						if(pdNew.dir != None){
							Cell cela = cell(pdNew.pos);
	                           					if(cela.id != -1  ){
	                           						Unit u = unit(cela.id);
	                           						if(u.type != 2 and u.player != 0  and  proper_moviment[pdNew.posP.i][pdNew.posP.j]){
	                           							proper_moviment[pdNew.posP.i][pdNew.posP.j] = false;
									return pdNew.ini;
	                           						}   	
							}
						}
						for( int k = 0; k < 4; ++k){
							ran = (2+ran)%8;
							Pos_Dir pdSeguent;
							pdSeguent.pos = pdNew.pos+ vdir[ran];
							pdSeguent.dir = vdir[ran]; 
						              if(pdNew.dir == None) {
						              	pdSeguent.ini = pdSeguent.dir;
						              	pdSeguent.posP = pdSeguent.pos;
						              }
						              else {
						             		pdSeguent.ini = pdNew.ini;
						               	pdSeguent.posP = pdNew.posP;
						              }
							if(not enc[pdSeguent.pos.i][pdSeguent.pos.j] ){
                               							if( cell(pdSeguent.pos).type != Wall  /*and proper_moviment[pdNew.posP.i][pdNew.posP.j] */) {
									Q.push(pdSeguent);
									enc[pdSeguent.pos.i][pdSeguent.pos.j] = true;
								}
							}
						}
					}
 				}

       	 return None;
	}

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
			command(k[j], bfs(k[j], cell_segura, proper_moviment));
		} 

		command(w[0], bfs(w[0], cell_segura, proper_moviment));
		command(w[1], bfs(w[1],cell_segura, proper_moviment));
	}
};

RegisterPlayer(PLAYER_NAME);