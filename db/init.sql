DROP TABLE IF EXISTS users;
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
