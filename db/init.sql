DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS mitglied;
DROP TABLE IF EXISTS boats;
DROP TABLE IF EXISTS Plz;
DROP TABLE IF EXISTS Personen;

CREATE TABLE users (
  username TEXT PRIMARY KEY NOT NULL,
  fullname TEXT,
  email    TEXT UNIQUE NOT NULL);

INSERT INTO users (username, fullname, email)
VALUES
('darin', 'Darin Darinov', 'baim@d.bg'),
('gogoe', 'Ivan Petkanov', 'momo@g.bg'),
('boiko', 'Boiko Morozov', 'hubo@b.bg');

CREATE TABLE if not exists 'Plz' (
  'PlzId'	INTEGER NOT NULL,
  'PlzNummer'	INTEGER NOT NULL UNIQUE,
  'PlzOrt'	TEXT NOT NULL,
  PRIMARY KEY('PlzId' AUTOINCREMENT));

/* добра идея ми изглежда по-голямата част от нашата таблица member да е тази от Personen */
CREATE TABLE if not exists 'Personen' (
  'PId'		INTEGER NOT NULL,
  'PName'	TEXT NOT NULL,
  'PAdr'	TEXT NOT NULL,
  'PTelnr'	TEXT NOT NULL,
  'PPlzFK'	INTEGER NOT NULL,
  PRIMARY KEY('PId' AUTOINCREMENT),
  FOREIGN KEY('PPlzFK') REFERENCES 'Plz'('PlzId'));

delete from Personen;
delete from Plz;
insert into Plz (PlzNummer,PlzOrt) values (1100,'Wien');
insert into Plz (PlzNummer,PlzOrt) values (1200,'Wien');
insert into Plz (PlzNummer,PlzOrt) values (3100,'St.Pölten');
insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Mary','Weg 1','123', (select PlzId from Plz where PlzNummer=1200));
insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Peter','Strasse 1','456', (select PlzId from Plz where PlzNummer=1100));
insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Fritz','Weg 2','789', (select PlzId from Plz where PlzNummer=3100));

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
  'firstname'	    TEXT NOT NULL,
  'lastname'	    TEXT,
  'birthdate'     DATE,
  'membershipid'  INTEGER NOT NULL,
  'typ'           TEXT CHECK (typ in  ('guest', 'athlete', 'trainer', 'manager', 'amateur')) NOT NULL DEFAULT 'guest',
  PRIMARY KEY('id' AUTOINCREMENT),
  FOREIGN KEY('membershipid') REFERENCES 'membership'('id')
);

/* объркващо е, лодките трябва да имам някакво ID с което да се различават една от друга */
CREATE TABLE 'boats' (
  id             INTEGER,
  price          INTEGER,
  herstelldatum  DATE NULL DEFAULT NULL,
  typ            TEXT CHECK (typ      in  ('canu', 'cayak', 'para-canu', 'para-cayak')) NOT NULL DEFAULT 'canu',
  material       TEXT CHECK (material in  ('wood', 'fabric', 'carbon'))                 NOT NULL DEFAULT 'wood',
  besitz         TEXT CHECK (besitz   in  ('private', 'sponsored', 'club'))             NOT NULL DEFAULT 'club',
  PRIMARY KEY('id' AUTOINCREMENT)
);

insert into boats (price,herstelldatum,typ,material,besitz) values (10000,"2020-11-24",'canu',      'fabric','sponsored');
insert into boats (price,herstelldatum,typ,material,besitz) values ( 8000,"2023-01-23",'para-canu', 'fabric','club');
insert into boats (price,herstelldatum,typ,material,besitz) values (14500,"2022-05-06",'cayak',     'fabric','club');
insert into boats (price,herstelldatum,typ,material,besitz) values ( 9900,"2015-12-09",'cayak',     'carbon','private');
insert into boats (price,herstelldatum,typ,material,besitz) values (11000,"2004-03-04",'canu',      'wood',  'club');
insert into boats (price,herstelldatum,typ,material,besitz) values (11500,"2005-07-20",'para-cayak','fabric','private');
insert into boats (price,herstelldatum,typ,material,besitz) values (14000,"2012-10-10",'canu',      'fabric','private');

/* ------------------------- Enumerated Types  ------------------------- */

CREATE TABLE if not exists membershiptype (
  id    INTEGER NOT NULL,
  type  TEXT NOT NULL UNIQUE,
  PRIMARY KEY(id AUTOINCREMENT));

insert into membershiptype (type) values ('guest'), ('athlete'), ('trainer'), ('manager'), ('amateur');

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

