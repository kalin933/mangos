-- UTGARDE PINNACLE instance template

-- Utgarde Pinnacle::Svala
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '1', `maxdmg` = '1', `attackpower` = '1', `mechanic_immune_mask` = '1073463287', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '315000', `maxhealth` = '315000', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21', `AIName` = '', `Scriptname` = 'boss_svala' WHERE `entry` IN (26668);
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '1', `maxdmg` = '1', `attackpower` = '1', `dmg_multiplier` = '13', `mechanic_immune_mask` = '1073463287', `minlevel` = '82', `maxlevel` = '82', `minhealth` = '431392', `maxhealth` = '431392', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (30810);
-- Utgarde Pinnacle::svala ritual channelerer
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '8121', `maxhealth` = '8121', `minmana` = '15976', `maxmana` = '15976',`AIName` = '', `Scriptname` = 'npc_svala_channeler' WHERE `entry` IN (27281);
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '81', `maxlevel` = '81', `minhealth` = '13033', `maxhealth` = '13033', `minmana` = '16324', `maxmana` = '16324' WHERE `entry` IN (30804);


-- Utgarde Pinnacle::Grouf not used in event for  now
-- DELETE FROM creature WHERE id = '26893';

-- Skadi the Ruthless(N)
UPDATE `creature_template` SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287, `AIName` = '', `Scriptname` = 'boss_skadi' WHERE `entry` IN (26693);
-- Skadi the Ruthless(H)
UPDATE `creature_template` SET `mechanic_immune_mask` = mechanic_immune_mask|1073463287 WHERE `entry` IN (30807);
-- Ymirjar Harpooner(N)
-- Ymirjar Witch Doctor(N)
-- Ymirjar Warrior(N)
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '18262', `maxhealth` = '18262', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000' WHERE `entry` IN (26692,26690,26691);
-- Ymirjar Harpooner(H)
-- Ymirjar Witch Doctor(H)
-- Ymirjar Warrior(H)
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `minhealth` = '26066', `maxhealth` = '26066', `minlevel` = '80', `maxlevel` = '81', `armor` = '4000', `mindmg` = '300', `maxdmg` = '400', `attackpower` = '2000', `dmg_multiplier` ='7.5' WHERE `entry` IN (30819,30823,30822);
-- Ymirjar Witch Doctor(N)
UPDATE `creature_template` SET `minmana` = '4080', `maxmana` = '4080' WHERE `entry` IN (26691);

-- Utgarde Pinnacle::Skadi harpoonlancher
UPDATE gameobject_template SET ScriptName = 'go_skaldi_harpoonluncher' WHERE entry IN (192175,192176,192177);

-- Avengering Spirit Summoner
UPDATE creature_template SET 
-- invisible
modelid_A = 11686,
modelid_H = 11686,
unit_flags = unit_flags|33554432|2,
ScriptName = '', AIName = 'EventAI' WHERE entry = 27392;

DELETE FROM creature_ai_scripts WHERE creature_id = 27392;
INSERT INTO creature_ai_scripts VALUES 
(2739201,27392,11,0,100,6, 0,0,0,0, 11,48593,0,0,0,0,0,0,0,0,0,0,'Avengering Spirit Summoner - Visual Effect'),
(2739202,27392,1,0,100,6, 8000,8000,0,0, 11,48592,0,0, 0,0,0,0, 0,0,0,0,'Avengering Spirit Summoner - Summon Spirit'),
(2739203,27392,1,0,100,6, 9000,9000,0,0, 37,0,0,0, 0,0,0,0, 0,0,0,0,'Avengering Spirit Summoner - ForcedDespawn');