DELETE FROM `spell_script_target` WHERE `entry` IN (26333,26334,26335,26336,26337,26338,26344,26351,26345,26352,26346,26353,26347,26354,26348,26355,26349,26356,26291,26292,26293,26286,26294,26295);
INSERT INTO `spell_script_target` VALUES 
(26333,0,180868),
(26334,0,180868),
(26335,0,180868),
(26336,0,180868),
(26337,0,180868),
(26338,0,180868),
(26344,0,180868),
(26351,0,180868),
(26345,0,180868),
(26352,0,180868),
(26346,0,180868),
(26353,0,180868),
(26347,0,180868),
(26354,0,180868),
(26348,0,180868),
(26355,0,180868),
(26349,0,180868),
(26356,0,180868),
(26291,0,180868),
(26292,0,180868),
(26293,0,180868),
(26286,0,180868),
(26294,0,180868),
(26295,0,180868),
(26334,0,180771),
(26333,0,180771),
(26335,0,180771),
(26336,0,180771),
(26337,0,180771),
(26338,0,180771),
(26344,0,180771),
(26351,0,180771),
(26345,0,180771),
(26352,0,180771),
(26346,0,180771),
(26353,0,180771),
(26347,0,180771),
(26354,0,180771),
(26348,0,180771),
(26355,0,180771),
(26349,0,180771),
(26356,0,180771),
(26291,0,180771),
(26292,0,180771),
(26293,0,180771),
(26286,0,180771),
(26294,0,180771),
(26295,0,180771);

-- Pat's Firework Guy
UPDATE `creature_template` SET 
`ScriptName` = 'mob_eventai',
`faction_a` = 35,
`faction_h` = 35
WHERE `entry` IN
(15882,15883,15879,15880,15881,15884,15885,15886,15887,15888,15889,15890);

DELETE FROM `spell_script_target` WHERE `entry` IN (26304,26325,26326,26327,26328,26329,26488,26490,26516,26517,26518,26519);
INSERT INTO `spell_script_target` VALUES
(26304,0,180772),
(26325,0,180772),
(26326,0,180772),
(26327,0,180772),
(26328,0,180772),
(26329,0,180772),
(26488,0,180772),
(26490,0,180772),
(26516,0,180772),
(26517,0,180772),
(26518,0,180772),
(26519,0,180772),
(26304,0,180859),
(26325,0,180859),
(26326,0,180859),
(26327,0,180859),
(26328,0,180859),
(26329,0,180859),
(26488,0,180859),
(26490,0,180859),
(26516,0,180859),
(26517,0,180859),
(26518,0,180859),
(26519,0,180859),
(26304,0,180869),
(26325,0,180869),
(26326,0,180869),
(26327,0,180869),
(26328,0,180869),
(26329,0,180869),
(26488,0,180869),
(26490,0,180869),
(26516,0,180869),
(26517,0,180869),
(26518,0,180869),
(26519,0,180869);

-- Pat's Firework Cluster
UPDATE `creature_template` SET 
`ScriptName` = 'mob_eventai', 
`faction_a` = 35,
`faction_h` = 35 
WHERE `entry` IN
(15918,15872,15873,15874,15875,15876,15877,15911,15912,15913,15914,15915,15916);


REPLACE INTO `creature_ai_scripts` VALUES
(1588201,15882,1,0,100,0,0,0,0,0, 11,26347,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - RED'),
(1588301,15883,1,0,100,0,0,0,0,0, 11,26349,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - YELLOW'),
(1587901,15879,1,0,100,0,0,0,0,0, 11,26344,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - BLUE'),
(1588001,15880,1,0,100,0,0,0,0,0, 11,26345,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - GREEN'),
(1588101,15881,1,0,100,0,0,0,0,0, 11,26346,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - PURPLE'),
(1588401,15884,1,0,100,0,0,0,0,0, 11,26348,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - WHITE'),
(1588501,15885,1,0,100,0,0,0,0,0, 11,26351,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - BLUE BIG'),
(1588601,15886,1,0,100,0,0,0,0,0, 11,26352,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - GREEN BIG'),
(1588701,15887,1,0,100,0,0,0,0,0, 11,26353,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - PURPLE BIG'),
(1588801,15880,1,0,100,0,0,0,0,0, 11,26354,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - RED BIG'),
(1588901,15889,1,0,100,0,0,0,0,0, 11,26355,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - WHITE BIG'),
(1589001,15890,1,0,100,0,0,0,0,0, 11,26356,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Guy - YELLOW BIG');

REPLACE INTO `creature_ai_scripts` VALUES
(1587201,15872,1,0,100,1,0,0,500,500, 11,26344,0,1, 0,0,0,0, 0,0,0,0,'Pats Firework Cluster Guy (BLUE)'),
(1587301,15873,1,0,100,1,0,0,500,500, 11,26347,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (RED)'),
(1587401,15874,1,0,100,1,0,0,500,500, 11,26345,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (GREEN)'),
(1587501,15875,1,0,100,1,0,0,500,500, 11,26346,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (PURPLE)'),
(1587601,15876,1,0,100,1,0,0,500,500, 11,26348,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (WHITE)'),
(1587701,15877,1,0,100,1,0,0,500,500, 11,26349,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (YELLOW)'),
(1591101,15911,1,0,100,1,0,0,500,500, 11,26351,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (BLUE BIG)'),
(1591201,15912,1,0,100,1,0,0,500,500, 11,26352,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (GREEN BIG)'),
(1591301,15913,1,0,100,1,0,0,500,500, 11,26353,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (PURPLE BIG)'),
(1591401,15914,1,0,100,1,0,0,500,500, 11,26354,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (RED BIG)'),
(1591501,15915,1,0,100,1,0,0,500,500, 11,26355,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (WHITE BIG)'),
(1591601,15916,1,0,100,1,0,0,500,500, 11,26356,0,1, 0,0,0,0, 0,0,0,0, 'Pats Firework Cluster Guy (YELLOW BIG)');


-- Large Rocket Recipes
DELETE FROM `item_loot_template` WHERE `entry` = 21742;
INSERT INTO `item_loot_template` VALUES
(21742,21729,100,0,1,1,0,0,0),
(21742,21728,100,0,1,1,0,0,0),
(21742,21727,100,0,1,1,0,0,0);