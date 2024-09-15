# Project: rowingclub (old: viena)

## Set the database in directory db:

```css
sqlite3 viena.db < init.sql
```

## Set environment variable for the absolute path of the database file:

```diff
+ Linux based systems terminal:
- export MYDB=<absolute_path>

+ Qt Creator:
- Edit > Preferences > Environment > System (tab) and change the Environment by adding MYDB=<absolute_path> line
```

## Compile

```css
qmake && make
```

## Run

```css
./viena
```
