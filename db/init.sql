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

CREATE TABLE if not exists 'membershiptypes' (
  'memberid'	INTEGER NOT NULL,
  'mtype'	TEXT NOT NULL UNIQUE,
  PRIMARY KEY('memberid' AUTOINCREMENT));

/* объркващо е, лодките трябва да имам някакво ID с което да се различават една от друга */
CREATE TABLE 'boats' (
  price          INTEGER,
  herstelldatum  DATE NULL DEFAULT NULL,
  typ            TEXT CHECK (typ      in  ('canu', 'cayak', 'para-canu', 'para-cayak')) NOT NULL DEFAULT 'canu',
  material       TEXT CHECK (material in  ('wood', 'fabric', 'carbon'))                 NOT NULL DEFAULT 'wood',
  besitz         TEXT CHECK (besitz   in  ('private', 'sponsored', 'club'))             NOT NULL DEFAULT 'club'
);

insert into boats (price,herstelldatum,typ,material,besitz) values (10000,"2020-11-24",'canu','fabric','club');

insert into membershiptypes (mtype) values ('guest'), ('athlete'), ('trainer'), ('manager'), ('amateur');

