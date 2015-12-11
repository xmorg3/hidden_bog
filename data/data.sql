PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE npc( mapid integer, name text, gender integer, 
health integer, healthmax integer, image text, faction text,
hitdice integer, hitbonus integer, damagedice integer,
damage bonus integer, weapon text, lootlist text, talklist text);
INSERT INTO "npc" VALUES(1000,'a pirate',0,8,8,'fpirate_01.png','pirate',1,0,1,1,'saber','pirate','female_pirate');
INSERT INTO "npc" VALUES(1001,'a pirate',1,8,8,'mpirate_01.png','pirate',1,0,1,1,'saber','pirate','male_pirate');
INSERT INTO "npc" VALUES(1002,'tentacle worm',2,20,20,'tentworm_01.png','none',1,3,1,-1,'barbs','tentacle_worm','none');
INSERT INTO "npc" VALUES(1003,'wreched undead',2,12,12,'undead_01.png','none',1,-1,1,2,'none','lessor_undead','none');
COMMIT;
