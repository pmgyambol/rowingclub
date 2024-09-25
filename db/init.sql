DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS mitglied;
DROP TABLE IF EXISTS boats;
DROP TABLE IF EXISTS gym;
DROP TABLE IF EXISTS cardios;
DROP TABLE IF EXISTS tarining;
DROP TABLE IF EXISTS еinkommen;
DROP TABLE IF EXISTS аufwand;

CREATE TABLE users (
  username TEXT PRIMARY KEY NOT NULL,
  fullname TEXT,
  email    TEXT UNIQUE NOT NULL);

INSERT INTO users (username, fullname, email)
VALUES
('darin', 'Darin Darinov', 'baim@d.bg'),
('gogoe', 'Ivan Petkanov', 'momo@g.bg'),
('boiko', 'Boiko Morozov', 'hubo@b.bg');

CREATE TABLE 'membership' (
  'id'     INTEGER,
  'start'  DATE,
  'end'    DATE,
  'fee'    INTEGER
);

CREATE TABLE 'membershiphistory' (
  'id'           INTEGER,
  'memberid'     INTEGER,
  'membershipid' INTEGER
);

CREATE TABLE if not exists mitglied (
  'id'            INTEGER NOT NULL,
  'firstname'     TEXT NOT NULL,
  'lastname'      TEXT,
  'sex'           TEXT CHECK (sex in  ('male', 'female', 'unknown')) NOT NULL DEFAULT 'unknown',
  'birthdate'     DATE,
  'nationality'   TEXT CHECK (nationality in  ('AT', 'EU', 'Other')) NOT NULL DEFAULT 'AT',
  'membershipid'  INTEGER,
  'membersince'   DATE,
  'address'       TEXT NOT NULL,
  'email'         TEXT,
  'typ'           TEXT CHECK (typ in  ('guest', 'athlete', 'trainer', 'manager', 'amateur')) NOT NULL DEFAULT 'guest',
  PRIMARY KEY('id' AUTOINCREMENT),
  FOREIGN KEY('membershipid') REFERENCES 'membership'('id')
);

/* объркващо е, лодките трябва да имам някакво ID с което да се различават една от друга */
CREATE TABLE if not exists 'boats' (
  id             INTEGER,
  price          INTEGER,
  herstelldatum  DATE NULL DEFAULT NULL,
  typ            TEXT CHECK (typ      in  ('canu', 'cayak', 'para-canu', 'para-cayak')) NOT NULL DEFAULT 'canu',
  material       TEXT CHECK (material in  ('wood', 'fabric', 'carbon'))                 NOT NULL DEFAULT 'wood',
  besitz         TEXT CHECK (besitz   in  ('private', 'sponsored', 'club'))             NOT NULL DEFAULT 'club',
  PRIMARY KEY('id' AUTOINCREMENT)
);

/* ----------------------------------- trainieren ----------------------------------- */

CREATE TABLE if not exists 'training' (
  id                     INTEGER,
  boat 		               INTEGER default 0,
  gym		                 INTEGER default 0,
  cardio	               INTEGER default 0,
  PRIMARY KEY('id' AUTOINCREMENT)
);

CREATE TABLE if not exists 'gym' (
  id             	       INTEGER,
  pushups        	       INTEGER default 0,
  plank 	     	         INTEGER default 0,
  squat 	     	         INTEGER default 0,
  benchPress             INTEGER default 0,
  deadlift               INTEGER default 0,
  pullUp 	     	         INTEGER default 0,
  legPress 	     	       INTEGER default 0,
  tricepPushDown 	       INTEGER default 0,
  dumbbellRow 	         INTEGER default 0,
  seatedRow 	           INTEGER default 0,
  PRIMARY KEY('id' AUTOINCREMENT)
);

CREATE TABLE if not exists 'cardios' (
  id                     INTEGER,
  paddelErgometerCanu    INTEGER default 0,
  paddelErgometerKayak   INTEGER default 0,
  running                INTEGER default 0,
  bycicling              INTEGER default 0,
  PRIMARY KEY('id' AUTOINCREMENT)
);

/* ----------------------------------- Finanzen ----------------------------------- */

CREATE TABLE if not exists 'gleichgewicht' (
  id                     INTEGER,
  startdatum             DATE,
  enddatum               DATE,
  gesamteinkommen        DOUBLE,
  gesamtkosten           DOUBLE,
  gesamtsaldo            DOUBLE,
  PRIMARY KEY('id' AUTOINCREMENT)
);

CREATE TABLE if not exists 'einkommen' (
  id                     INTEGER,
  mitgliedsbeitrag       DOUBLE,
  bootsverleih           DOUBLE,
  gastebeitrag           DOUBLE,
  bootshausmieten        DOUBLE,
  foderationssubvention  DOUBLE,
  werbung                DOUBLE, 
  freiearbeit            DOUBLE,
  datum                  DATE NOT NULL DEFAULT (DATE('now')),
  PRIMARY KEY('id' AUTOINCREMENT)
);

CREATE TABLE if not exists 'aufwand' (
  id                     INTEGER,
  fixedcost              DOUBLE,
  salaries               DOUBLE,
  rent                   DOUBLE,
  electricity            DOUBLE,
  water                  DOUBLE,
  heating                DOUBLE,
  amortization           DOUBLE,
  gekauftesMaterial      DOUBLE,
  datum                  DATE NOT NULL DEFAULT (DATE('now')),
  PRIMARY KEY('id' AUTOINCREMENT)
);

/* ===================================================================== */
/* ------------------------- Enumerated Types  ------------------------- */
/* ===================================================================== */

/* -----------------------==--- mitglied ---==-------------------------- */

CREATE TABLE if not exists membershiptype (
  id    INTEGER NOT NULL,
  type  TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into membershiptype (type) values ('guest'), ('athlete'), ('trainer'), ('manager'), ('amateur');

CREATE TABLE if not exists sextype (
  id   INTEGER NOT NULL,
  type TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into sextype (type) values ('male'), ('female'), ('unknown');

CREATE TABLE if not exists nationalitytype (
  id   INTEGER NOT NULL,
  type TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into nationalitytype (type) values ('AT'), ('EU'), ('Other');

/* ------------------------==--- boat ---==--------------------------- */

CREATE TABLE if not exists materialtype (
  id   INTEGER NOT NULL,
  type TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into materialtype (type) values ('wood'), ('carbon'), ('fabric');

CREATE TABLE if not exists boattype (
  id   INTEGER NOT NULL,
  type TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into boattype (type) values ('canu'), ('cayak'), ('para-canu'), ('para-cayak');

CREATE TABLE if not exists besitztype (
  id   INTEGER NOT NULL,
  type TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into besitztype (type) values ('private'), ('sponsored'), ('club');

/* =============================================================== */
/* ------------------------- Insertions  ------------------------- */
/* =============================================================== */

insert into mitglied (firstname,lastname,sex,birthdate,nationality,membersince,address,email,typ)
values
('Robert','Mustermann','male',  '2004-03-04','AT','2020-03-04','Wien, Krauserstraße 38, 1050','robert.mustermann@email.mail', 'amateur' ),
('Max',   'Mustermann','female','2002-05-08','AT','2022-03-04','Graz Krauserstraße 38 1050',  'max.mustermann@email.mail',    'athlete' );

insert into boats (price,herstelldatum,typ,material,besitz) 
values
(10000,'2020-11-24','canu',      'fabric','sponsored'),
( 8000,'2023-01-23','para-canu', 'fabric','club'),
(14500,'2022-05-06','cayak',     'fabric','club'),
( 9900,'2015-12-09','cayak',     'carbon','private'),
(11000,'2004-03-04','canu',      'wood',  'club'),
(11500,'2005-07-20','para-cayak','fabric','private'),
(14000,'2012-10-10','canu',      'fabric','private');

insert into gym      (pushups,plank,squat,benchPress,deadlift, pullUp, legPress, tricepPushDown, dumbbellRow, seatedRow) values (10,20,30,40,50,60,70,80,90,1);
insert into cardios  (paddelErgometerCanu, paddelErgometerKayak, running, bycicling) values (10,10,15,30);
insert into training (boat,cardio) values (1,2), (1,4);

insert into einkommen (mitgliedsbeitrag, bootsverleih, gastebeitrag, bootshausmieten, foderationssubvention, werbung, freiearbeit)
values
(10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0),
(11.1, 22.2, 33.3, 44.4, 55.5, 66.6, 77.7);

insert into aufwand (fixedcost, salaries, rent, electricity, water, heating, amortization, gekauftesMaterial)
values
(10.8, 20.7, 30.6, 40.5, 50.4, 60.3, 70.2, 80.1),
(91.1, 92.2, 93.3, 94.4, 95.5, 96.6, 97.7, 98.8);