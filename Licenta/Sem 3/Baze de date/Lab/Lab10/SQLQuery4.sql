-- a table that contains the current version of the database schema
CREATE TABLE VersionTable (
	version INT
)

INSERT INTO VersionTable 
VALUES
	(1) -- this is the initial version


-- a table that contains the initial version, the version after the execution of the procedure and the procedure that changes the table in this way
CREATE TABLE ProcedureTable (
	initial_version INT,
	final_version INT,
	procedure_name VARCHAR(MAX),
	PRIMARY KEY (initial_version, final_version)
)

INSERT INTO ProcedureTable
VALUES
	(1, 2, 'setFeaturingFromPerformingDecimal'),
	(2, 1, 'setFeaturingFromPerformingInt'),
	(2, 3, 'addNumberOfStudiosToLabels'), 
	(3, 2, 'removeNumberOfStudiosFromLabels'),
	(3, 4, 'addDefaultToFeaturingFromPerforming'),
	(4, 3, 'removeDefaultFromFeaturingFromPerforming'),
	(4, 5, 'addBestSongsOfTheYear'),
	(5, 4, 'dropBestSongsOfTheYear'),
	(5, 6, 'addArtistIDAndSongIDPrimaryKeyWeeklyTop10'),
	(6, 5, 'removeArtistIDAndSongIDPrimaryKeyWeeklyTop10'),
	(6, 7, 'newCandidateKeyArtist'),
	(7, 6, 'removeCandidateKeyArtist'),
	(7, 8, 'newForeignKeyWeeklyTop10'),
	(8, 7, 'removeForeignKeyWeeklyTop10')