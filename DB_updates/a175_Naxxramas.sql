-- NAXXRAMAS

-- Set to not working boses NON ATTACKABLE FLAG 
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE `entry` IN (15954,15936,16011,16061,16060,16064,16065,30549,16063,16028,15931,15932,15928,15989,15990,29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600);
-- North 15954,
-- Heigan 15936,
-- Loatheb 16011,
-- Instructor 16061,
-- Gothik 16060,
-- Horsameni 16064, 16065, 30549, 16063,
-- Patchewrk 16028,
-- Grobulus 15931,
-- Gluth 15932,
-- Tadius 15928,
-- Saphiron 15989,
-- Kelthuzad 15990
-- 25ppl ids
-- 29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600,


-- Arachnid Quarter::Worshippers and folowers
DELETE FROM `creature` WHERE `id` IN (16506);
UPDATE creature_template SET `minmana` ='58750', `maxmana` = '58750' WHERE `entry` IN (29273);

-- NAXXRAMAS LOOT

DELETE FROM creature_loot_template WHERE entry IN (29249,29268,29278);

-- Arachnid Quarter::AnubRekhan 25ppl
-- Arachnid Quarter::Faerlina 25ppl
-- Arachnid Quarter::Maexxna 25ppl

UPDATE creature_template SET `lootid` = entry WHERE `entry` IN (29249,29268,29278);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- totaly random groups - has to be redone
-- Arachnid Quarter::AnubRekhan 25ppl
('29249', '39712', '0', '1', '1', '1', '0', '0', '0'),
('29249', '39716', '0', '1', '1', '1', '0', '0', '0'),
('29249', '39714', '0', '1', '1', '1', '0', '0', '0'),
('29249', '39717', '0', '1', '1', '1', '0', '0', '0'),
('29249', '39722', '0', '2', '1', '1', '0', '0', '0'),
('29249', '39718', '0', '2', '1', '1', '0', '0', '0'),
('29249', '39701', '0', '2', '1', '1', '0', '0', '0'),
('29249', '39720', '0', '2', '1', '1', '0', '0', '0'),
('29249', '39719', '0', '2', '1', '1', '0', '0', '0'),
('29249', '39704', '0', '3', '1', '1', '0', '0', '0'),
('29249', '39703', '0', '3', '1', '1', '0', '0', '0'),
('29249', '39706', '0', '3', '1', '1', '0', '0', '0'),
('29249', '39721', '0', '3', '1', '1', '0', '0', '0'),
('29249', '39702', '0', '3', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Faerlina 25ppl
('29268', '39726', '0', '1', '1', '1', '0', '0', '0'),
('29268', '39727', '0', '1', '1', '1', '0', '0', '0'),
('29268', '39725', '0', '1', '1', '1', '0', '0', '0'),
('29268', '39723', '0', '1', '1', '1', '0', '0', '0'),
('29268', '39731', '0', '1', '1', '1', '0', '0', '0'),
('29268', '39734', '0', '2', '1', '1', '0', '0', '0'),
('29268', '39735', '0', '2', '1', '1', '0', '0', '0'),
('29268', '39729', '0', '2', '1', '1', '0', '0', '0'),
('29268', '39733', '0', '2', '1', '1', '0', '0', '0'),
('29268', '39757', '0', '2', '1', '1', '0', '0', '0'),
('29268', '39728', '0', '3', '1', '1', '0', '0', '0'),
('29268', '39756', '0', '3', '1', '1', '0', '0', '0'),
('29268', '39730', '0', '3', '1', '1', '0', '0', '0'),
('29268', '39732', '0', '3', '1', '1', '0', '0', '0'),
('29268', '39724', '2', '2', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Maexxna 25ppl
('29278', '40062', '0', '1', '1', '1', '0', '0', '0'),
('29278', '40063', '0', '1', '1', '1', '0', '0', '0'),
('29278', '39764', '0', '1', '1', '1', '0', '0', '0'),
('29278', '39768', '0', '1', '1', '1', '0', '0', '0'),
('29278', '40060', '0', '1', '1', '1', '0', '0', '0'),
('29278', '39760', '0', '2', '1', '1', '0', '0', '0'),
('29278', '39766', '0', '2', '1', '1', '0', '0', '0'),
('29278', '40061', '0', '2', '1', '1', '0', '0', '0'),
('29278', '39765', '0', '2', '1', '1', '0', '0', '0'),
('29278', '39758', '0', '2', '1', '1', '0', '0', '0'),
('29278', '39767', '0', '3', '1', '1', '0', '0', '0'),
('29278', '39763', '0', '3', '1', '1', '0', '0', '0'),
('29278', '39759', '0', '3', '1', '1', '0', '0', '0'),
('29278', '39761', '0', '3', '1', '1', '0', '0', '0'),
('29278', '39762', '0', '3', '1', '1', '0', '0', '0');