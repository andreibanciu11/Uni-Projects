-- a view with a SELECT statement that has a GROUP BY clause, 
--		operates on at least 2 different tables and contains at least one JOIN operator
-- a table with a single-column primary key and at least one foreign key
-- a table with a multicolumn primary key

GO
CREATE OR ALTER VIEW artistsAndSongs AS
	SELECT ArtistsTest.ArtistName, SongsTest.Title, SongsTest.NumberOfStreams
	FROM ArtistsTest 
	INNER JOIN PerformingTest ON ArtistsTest.ArtistID = PerformingTest.ArtistID
	INNER JOIN SongsTest ON PerformingTest.SongID = SongsTest.SongID
	WHERE SongsTest.NumberOfStreams >= 5000000
	GROUP BY ArtistsTest.ArtistName, SongsTest.Title, SongsTest.NumberOfStreams


GO
EXEC addToTables 'ArtistsTest'
EXEC addToTables 'PerformingTest'
EXEC addToTables 'SongsTest'
EXEC addToViews 'artistsAndSongs'
EXEC addToTests 'test3'
EXEC connectTableToTest 'ArtistsTest', 'test3', 500, 1
EXEC connectTableToTest 'SongsTest', 'test3', 500, 2
EXEC connectTableToTest 'PerformingTest', 'test3', 300, 3
EXEC connectViewToTest 'artistsAndSongs', 'test3'


GO
CREATE OR ALTER PROCEDURE populateTableArtistsTest (@numberOfRows INT) AS
	DECLARE @stringValue VARCHAR(50)
	WHILE @numberOfRows > 0 
	BEGIN
		EXEC generateRandomString @stringValue OUTPUT
		INSERT INTO ArtistsTest (ArtistID, ArtistName)
		VALUES (@numberOfRows, @stringValue)
		SET @numberOfRows = @numberOfRows - 1
	END


GO
CREATE OR ALTER PROCEDURE populateTableSongsTest (@numberOfRows INT) AS
	DECLARE @stringValue VARCHAR(50)
	WHILE @numberOfRows > 0 
	BEGIN
		EXEC generateRandomString @stringValue OUTPUT
		INSERT INTO SongsTest (SongID, Title, NumberOfStreams)
		VALUES (@numberOfRows, @stringValue, floor(rand() * 7) * 1000000)
		SET @numberOfRows = @numberOfRows - 1
	END


GO
CREATE OR ALTER PROCEDURE populateTablePerformingTest (@numberOfRows INT) AS
	DECLARE @stringValue VARCHAR(50)
	DECLARE @artistID INT
	DECLARE @songID INT
	WHILE @numberOfRows > 0 
	BEGIN
		EXEC generateRandomString @stringValue OUTPUT
		SET @artistID = (SELECT TOP 1 ArtistID FROM ArtistsTest ORDER BY NEWID())
		SET @songID = (SELECT TOP 1 SongID FROM SongsTest ORDER BY NEWID())
		WHILE EXISTS (SELECT * FROM PerformingTest WHERE ArtistID = @artistID AND SongID = @songID)
		BEGIN
			SET @artistID = (SELECT TOP 1 ArtistID FROM ArtistsTest ORDER BY NEWID())
			SET @songID = (SELECT TOP 1 SongID FROM SongsTest ORDER BY NEWID())
		END
		INSERT INTO PerformingTest(ArtistID, SongID)
		VALUES (@artistID, @songID)
		SET @numberOfRows = @numberOfRows - 1
	END