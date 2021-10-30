class carta {
	bool coperta;
	char valore;
	int moltiplicatore;
	public:
		carta () {coperta=true;valore='1';moltiplicatore=1;}
		carta (char v, int m) {valore=v;moltiplicatore=m;}
		
		bool get_coperta () {return coperta;}
		void set_coperta (bool c) {coperta=c;}
		
		char get_valore () {return valore;}
		void set_valore (char v) {valore=v;}
		
		int get_molt () {return moltiplicatore;}
		void set_molt (int m) {moltiplicatore=m;}
		
		void inizia_carta (char v, int m) {valore=v;moltiplicatore=m;}
};
