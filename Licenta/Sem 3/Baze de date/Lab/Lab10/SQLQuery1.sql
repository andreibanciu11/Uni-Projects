-- modify the type of a column
CREATE OR ALTER PROCEDURE setFeaturingFromPerformingDecimal
AS
    ALTER TABLE Performing ALTER COLUMN Featuring DECIMAL(1,0)
GO

CREATE OR ALTER PROCEDURE setFeaturingFromPerformingInt
AS
	ALTER TABLE Performing ALTER COLUMN Featuring INT
GO

-- add / remove a column
CREATE OR ALTER PROCEDURE addNumberOfStudiosToLabels
AS
	ALTER TABLE Labels ADD NumberOfStudios INT
GO

CREATE OR ALTER PROCEDURE removeNumberOfStudiosFromLabels
AS
	ALTER TABLE Labels DROP COLUMN NumberOfStudios
GO

-- add/remove a DEFAULT constraint
CREATE OR ALTER PROCEDURE addDefaultToFeaturingFromPerforming
AS
	ALTER TABLE Performing ADD CONSTRAINT default_exp DEFAULT(0) FOR Featuring
GO

CREATE OR ALTER PROCEDURE removeDefaultFromFeaturingFromPerforming
AS
	ALTER TABLE Performing DROP CONSTRAINT default_exp
GO

-- create/drop a table
CREATE OR ALTER PROCEDURE addBestSongsOfTheYear
AS
	CREATE TABLE BestSongsOfTheYear (
		PlaceID INT NOT NULL,
		ArtistID INT NOT NULL,
		SongID INT NOT NULL,
		CONSTRAINT PLACE_CONTEST_PRIMARY_KEY PRIMARY KEY(PlaceID),
		CONSTRAINT ARTIST_CONTEST_FOREIGN_KEY FOREIGN KEY (ArtistID)
        REFERENCES Artists (ArtistID),
		CONSTRAINT SONG_CONTEST_FOREIGN_KEY FOREIGN KEY (SongID)
        REFERENCES Songs (SongID)
	)
GO 

CREATE OR ALTER PROCEDURE dropBestSongsOfTheYear
AS
	DROP TABLE BestSongsOfTheYear
GO

-- add/remove a primary key
CREATE OR ALTER PROCEDURE addArtistIDAndSongIDPrimaryKeyWeeklyTop10
AS
	ALTER TABLE WeeklyTop10
		DROP CONSTRAINT PLACE_PRIMARY_KEY
	ALTER TABLE WeeklyTop10
		ADD CONSTRAINT ARTIST_SONG_PRIMARY_KEY PRIMARY KEY(ArtistID, SongID)
GO 

CREATE OR ALTER PROCEDURE removeArtistIDAndSongIDPrimaryKeyWeeklyTop10
AS
	ALTER TABLE WeeklyTop10
		DROP CONSTRAINT ARTIST_SONG_PRIMARY_KEY
	ALTER TABLE WeeklyTop10
		ADD CONSTRAINT PLACE_PRIMARY_KEY PRIMARY KEY(PlaceID)
GO

-- add/remove a candidate key
CREATE OR ALTER PROCEDURE newCandidateKeyArtist 
AS	
	ALTER TABLE Artists
		ADD CONSTRAINT ARTIST_CANDIDATE_KEY UNIQUE(ArtistName, Country, DOB)
GO

CREATE OR ALTER PROCEDURE removeCandidateKeyArtist
AS
	ALTER TABLE Artists
		DROP CONSTRAINT ARTIST_CANDIDATE_KEY
GO

-- add / remove a foreign key
CREATE OR ALTER PROCEDURE newForeignKeyWeeklyTop10 
AS
	ALTER TABLE WeeklyTop10
		ADD CONSTRAINT WEEKLY_FOREIGN_KEY FOREIGN KEY(PlaceID) REFERENCES Artists(ArtistID)
GO

CREATE OR ALTER PROCEDURE removeForeignKeyWeeklyTop10
AS
	ALTER TABLE WeeklyTop10
		DROP CONSTRAINT WEEKLY_FOREIGN_KEY
GO

-- procedure to bring the database to the specified version
CREATE OR ALTER PROCEDURE goToVersion(@newVersion INT) 
AS
	DECLARE @current_version INT
	DECLARE @procedureName VARCHAR(MAX)
	SELECT @current_version = version FROM VersionTable

	IF (@newVersion > (SELECT MAX(final_version) FROM ProcedureTable) OR @newVersion < 1)
		RAISERROR ('Bad version', 10, 1)
	ELSE
	BEGIN
		IF @newVersion = @current_version
			PRINT('You are already on this version!');
		ELSE
		BEGIN
			IF @current_version > @newVersion
			BEGIN
				WHILE @current_version > @newVersion 
					BEGIN
						SELECT @procedureName = procedure_name FROM ProcedureTable WHERE initial_version = @current_version AND final_version = @current_version-1
						PRINT('Executing ' + @procedureName);
						EXEC (@procedureName)
						SET @current_version = @current_version - 1
					END
			END

			IF @current_version < @newVersion
			BEGIN
				WHILE @current_version < @newVersion 
					BEGIN
						SELECT @procedureName = procedure_name FROM ProcedureTable WHERE initial_version = @current_version AND final_version = @current_version+1
						PRINT('Executing ' + @procedureName);
						EXEC (@procedureName)
						SET @current_version = @current_version + 1
					END
			END

			UPDATE versionTable SET version = @newVersion
		END
	END
GO

EXEC goToVersion 1

SELECT *
FROM VersionTable

SELECT *
FROM ProcedureTable
