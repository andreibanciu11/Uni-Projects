CREATE TABLE users (
  id INT PRIMARY KEY AUTO INCREMENT,
  username VARCHAR(50),
  password VARCHAR(50)
);

INSERT INTO users (id, username, password) VALUES
  (1, 'andrei.banciu', 'parola'),
  (2, 'user2', 'parola2'),
  (3, 'user3', 'parola3'),
  (4, 'user4', 'parola4'),
  (5, 'user5', 'parola5');

CREATE TABLE books (
  id INT PRIMARY KEY,
  author VARCHAR(100),
  title VARCHAR(100),
  number_of_pages INT,
  genre VARCHAR(50),
  userID INT,
  FOREIGN KEY (userID) REFERENCES users(id)
);

INSERT INTO books (id, author, title, number_of_pages, genre, userID) VALUES
  (1, 'Jane Austen', 'Pride and Prejudice', 432, 'Romance', 2),
  (2, 'George Orwell', '1984', 328, 'Dystopian', 3),
  (3, 'J.K. Rowling', 'Harry Potter and the Philosopher''s Stone', 352, 'Fantasy', 1),
  (4, 'Harper Lee', 'To Kill a Mockingbird', 336, 'Classic', 4),
  (5, 'Stephen King', 'The Shining', 688, 'Horror', 5),
  (6, 'J.R.R. Tolkien', 'The Lord of the Rings', 1178, 'Fantasy', 1),
  (7, 'Gillian Flynn', 'Gone Girl', 432, 'Mystery', 1),
  (8, 'Agatha Christie', 'Murder on the Orient Express', 256, 'Mystery', 1),
  (9, 'Gabriel Garcia Marquez', 'One Hundred Years of Solitude', 417, 'Magical Realism', 1),
  (10, 'Jane Austen', 'Emma', 512, 'Romance', 1),
  (11, 'Ernest Hemingway', 'The Old Man and the Sea', 127, 'Classic', 1);

SELECT * FROM books