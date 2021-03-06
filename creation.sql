

DROP TABLE SERIE CASCADE CONSTRAINTS;
CREATE TABLE SERIE
(
	TITRE	   	      VARCHAR2(40),
	ANNEE    	      VARCHAR2(4)      CONSTRAINT NN_SERIE_ANNEE    	 NOT NULL,
	PAYS	   	      VARCHAR2(25)	    CONSTRAINT NN_SERIE_PAYS     NOT NULL,
	DATE_CREATION	      DATE      	CONSTRAINT NN_SERIE_DATE    	 NOT NULL,
	CONSTRAINT PK_SERIE_TIT_ANNE       PRIMARY KEY (TITRE)
);

DROP TABLE SAISON CASCADE CONSTRAINTS;
CREATE TABLE SAISON
(
	ID_SAISON 	  NUMBER(2)      CONSTRAINT PK_SAIS_ID PRIMARY KEY,
	TITRE		  VARCHAR2(40),
	CONSTRAINT FK_TIT_SER FOREIGN KEY(TITRE) REFERENCES SERIE
);

DROP TABLE PERSONNE CASCADE CONSTRAINTS;
CREATE TABLE PERSONNE
(
	NOMP                VARCHAR2(25)    CONSTRAINT NN_PERSONNE_NOMP           NOT NULL,
	PRENOMP             VARCHAR2(25)    CONSTRAINT NN_PERSONNE_PRENOMP        NOT NULL,
	CONSTRAINT PK_PERSONNE_NOM_PRE          PRIMARY KEY(NOMP,PRENOMP)
);

DROP TABLE UTILISATEURS CASCADE CONSTRAINTS;
CREATE TABLE UTILISATEURS
(	PSEUDO	            VARCHAR2(25)	CONSTRAINT PK_UTILI_PSEUDO PRIMARY KEY,
	DATE_INSCRIPTION    DATE         	CONSTRAINT NN_UTILI_DATE   	NOT NULL,
	AGE	            NUMBER(2)	    CONSTRAINT NN_UTILI_AGE   		NOT NULL,
	SEXE	            VARCHAR2(1)	  CONSTRAINT CK_UTILI_SEXE  	 CHECK(SEXE IN ('M','F')));


DROP TABLE EPISODE CASCADE CONSTRAINTS;
CREATE TABLE EPISODE
(
	TITREEP       	  VARCHAR2(25)	   CONSTRAINT PK_EPISO_TITRE PRIMARY KEY,
	DUREE       	  NUMBER(4)	       CONSTRAINT NN_EPISO_DURE 	NOT NULL,
	DATE_DIFFU        DATE             CONSTRAINT NN_EPISO_DATE  		NOT NULL,
	ID_SAISON         NUMBER,
	RESUME		  VARCHAR2(100)	NOT NULL,
	TITRE	          VARCHAR2(25),
	CONSTRAINT FK_EPI_ID_SAIS FOREIGN KEY (ID_SAISON) REFERENCES SAISON,
	CONSTRAINT FK_EPI_TIT_ANN_SERIE   FOREIGN KEY (TITRE) REFERENCES SERIE);


DROP TABLE REALISATEURS CASCADE CONSTRAINTS;
CREATE TABLE REALISATEURS
(
	NOMP 	    	  VARCHAR2(25),
	PRENOMP  	  VARCHAR2(25),
	TITREEP		  VARCHAR2(25),
	CONSTRAINT PK_REALI_NOM_PRE_TIT PRIMARY KEY (NOMP,PRENOMP,TITREEP) ,
	CONSTRAINT FK_REALI_NOM_PRE_PERSO  FOREIGN KEY (NOMP,PRENOMP) REFERENCES PERSONNE,
	CONSTRAINT FK_REALI_TIT_EPI        FOREIGN KEY (TITREEP)      REFERENCES EPISODE
);

DROP TABLE ACTEURS CASCADE CONSTRAINTS;
CREATE TABLE ACTEURS
(
	NOMP 	   	  VARCHAR2(25),
	PRENOMP  	  VARCHAR2(25),
	TITREEP		  VARCHAR2(50),
	CONSTRAINT PK_ACTE_NOM_PRE_TIT PRIMARY KEY (NOMP,PRENOMP,TITREEP) ,
	CONSTRAINT FK_ACTEU_NOM_PRE_PERSO  FOREIGN KEY (NOMP,PRENOMP) REFERENCES PERSONNE,
	CONSTRAINT FK_ACTEU_TIT_EPI        FOREIGN KEY (TITREEP)      REFERENCES EPISODE
);

DROP TABLE PRODUCTEURS CASCADE CONSTRAINTS;
CREATE TABLE PRODUCTEURS
(
	NOMP 	    	VARCHAR2(25),
	PRENOMP  	VARCHAR2(25),
	TITRE	  	VARCHAR2(40),
	CONSTRAINT PK_PRODU_NOM_PRE_TIT PRIMARY KEY (NOMP,PRENOMP,TITRE) ,
	CONSTRAINT FK_PRODU_NOM_PRE_PERSO  FOREIGN KEY (NOMP,PRENOMP) REFERENCES PERSONNE,
	CONSTRAINT FK_PRODU_TIT_ANN_SERIE   FOREIGN KEY (TITRE) REFERENCES SERIE
);


DROP TABLE CREATEURS CASCADE CONSTRAINTS;
CREATE TABLE CREATEURS
(
	NOMP 	    	VARCHAR2(25),
	PRENOMP  	VARCHAR2(25),
	TITRE	  	VARCHAR2(40) ,
	CONSTRAINT PK_CREA_NOM_PRE_TIT PRIMARY KEY (NOMP,PRENOMP,TITRE) ,
	CONSTRAINT FK_CREA_NOM_PRE_PERSO  FOREIGN KEY (NOMP,PRENOMP) REFERENCES PERSONNE,
	CONSTRAINT FK_CREA_TIT_ANN_SERIE   FOREIGN KEY (TITRE) REFERENCES SERIE
);

---------------------------------------------------------------------------

DROP TABLE GENRE CASCADE CONSTRAINTS;
CREATE TABLE GENRE
(
	NOMG 		VARCHAR2(25)   CONSTRAINT PK_GENR_NOM PRIMARY KEY
);


DROP TABLE G_SERIE CASCADE CONSTRAINTS;
CREATE TABLE G_SERIE
(
	NOMG 		VARCHAR2(25),
	TITRE	  	VARCHAR2(40),
	CONSTRAINT PK_NOM_TIT_GSERIE   PRIMARY KEY (NOMG,TITRE) ,
	CONSTRAINT FK_G_SER_TIT_ANN_SERIE   FOREIGN KEY (TITRE) REFERENCES SERIE,
	CONSTRAINT FK_G_SER_NOM_SERIE       FOREIGN KEY  (NOMG)       REFERENCES GENRE
);

DROP TABLE NOTE_EP CASCADE CONSTRAINTS;
CREATE TABLE NOTE_EP
(
	 TITREEP	VARCHAR2(25),
	 PSEUDO	     	VARCHAR2(25),
	 NOTE		NUMBER,
	 COMMENTAIRE	VARCHAR2(100),
	 DATE_NOTE	DATE 	NOT NULL,
	 CONSTRAINT PK_NOT_SER_TIT_ANNEE PRIMARY KEY (PSEUDO,TITREEP),
	 CONSTRAINT FK_NOTE_EP_TITR_EPI FOREIGN KEY (TITREEP) REFERENCES EPISODE,
	 CONSTRAINT FK_NOTE_EP_PSEUDO FOREIGN KEY (PSEUDO) REFERENCES UTILISATEURS);




 DROP TABLE NOTE_SER CASCADE CONSTRAINTS;
 CREATE TABLE NOTE_SER
 (
	PSEUDO	     	 VARCHAR2(25),
	TITRE	       	 VARCHAR2(25),
	NOTE		 NUMBER,
	COMMENTAIRE	 VARCHAR2(100),
	DATE_NOTE	 DATE 	NOT NULL,
	CONSTRAINT PK_NOTSER_PSEU_TIT PRIMARY KEY (PSEUDO,TITRE),
	CONSTRAINT FK_NOTE_SER_TIT_ANN_SER FOREIGN KEY (TITRE)  REFERENCES SERIE,
	CONSTRAINT FK_NOTE_SER_PS  FOREIGN KEY (PSEUDO) REFERENCES UTILISATEURS
);


DROP TABLE COMMEN CASCADE CONSTRAINTS;
CREATE TABLE COMMEN
(
	 ID_COM    	NUMBER     CONSTRAINT  PK_COM_ID PRIMARY KEY,
	 PSEUDO	   	VARCHAR2(25),
	 ID_REPONSE 	NUMBER  ,
	 DATE_CO       DATE  ,
	 COMMENTAIRE VARCHAR2(100),
	 CONSTRAINT FK_COMMEN_PSEUDO  FOREIGN KEY (PSEUDO) REFERENCES UTILISATEURS);
