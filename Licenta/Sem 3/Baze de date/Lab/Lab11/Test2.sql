-- a view with a SELECT statement that operates on at least 2 different tables and contains at least one JOIN operator

GO
CREATE OR ALTER VIEW concertAtLeast2023 AS
	SELECT ConcertsTest.ConcertName, ConcertsTest.ConcertDate, ArtistsTest.ArtistName
	FROM ConcertsTest
	INNER JOIN ArtistsTest ON ConcertsTest.ConcertID = ArtistsTest.ArtistID
	WHERE ConcertsTest.ConcertDate > '2023-01-01'

GO
EXEC addToTables 'ConcertsTest'
EXEC addToTables 'ArtistsTest'
EXEC addToViews 'concertAtLeast2023'
EXEC addToTests 'test2'
EXEC connectTableToTest 'ConcertsTest', 'test2', 500, 1
EXEC connectTableToTest 'ArtistsTest', 'test2', 500, 2
EXEC connectViewToTest 'concertAtLeast2023', 'test2'


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
CREATE OR ALTER PROCEDURE populateTableConcertsTest (@numberOfRows INT) AS
	DECLARE @artistID INT
	DECLARE @stringValue VARCHAR(50)
	WHILE @numberOfRows > 0 
	BEGIN
		SET @artistID = (SELECT TOP 1 ArtistID FROM ArtistsTest ORDER BY NEWID())
		WHILE EXISTS (SELECT * FROM ConcertsTest WHERE SignedArtistID = @artistID)
		BEGIN
			SET @artistID = (SELECT TOP 1 ArtistID FROM ArtistsTest ORDER BY NEWID())
		END
		EXEC generateRandomString @stringValue OUTPUT
		DECLARE @StartDate AS date;
		DECLARE @EndDate AS date;
		SELECT @StartDate = '2019-01-01', -- Date Format - DD/MM/YYY
		@EndDate   = '2024-12-31';
		DECLARE @FinalDate AS date;

		SELECT @FinalDate = (SELECT DATEADD(DAY, RAND(CHECKSUM(NEWID()))*(1+DATEDIFF(DAY, @StartDate, @EndDate)),@StartDate));
		INSERT INTO ConcertsTest(ConcertID, ConcertName, ConcertDate, SignedArtistID)
		VALUES (@numberOfRows, @stringValue, @FinalDate, @artistID)
		SET @numberOfRows = @numberOfRows - 1
	END