-- a table with a single-column primary key and no foreign keys
-- a view with a SELECT statement operating on one table

GO
CREATE OR ALTER VIEW radiosWithMoreThan700000Users AS
	SELECT R.RadioName, R.NumberOfUsers
	FROM RadioTest R
	WHERE R.NumberOfUsers > 700000


GO
EXEC addToTables 'RadioTest'
EXEC addToViews 'radiosWithMoreThan700000Users'
EXEC addToTests 'test1'
EXEC connectTableToTest 'RadioTest', 'test1', 500, 1
EXEC connectViewToTest 'radiosWithMoreThan700000Users', 'test1'


GO
CREATE OR ALTER PROCEDURE populateTableRadioTest (@numberOfRows INT) AS
	DECLARE @stringValue VARCHAR(50)
	WHILE @numberOfRows > 0 
	BEGIN
		
		EXEC generateRandomString @stringValue OUTPUT
		INSERT INTO RadioTest(RadioFMID, RadioName, NumberOfUsers) 
		VALUES (@numberOfRows, @stringValue, floor(rand() * 7) * 1000000)
		SET @numberOfRows = @numberOfRows - 1
	END
