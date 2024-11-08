CREATE DATABASE Biblioteca;
USE Biblioteca;

CREATE TABLE Libro(
    IdLibro INT NOT NULL ,
    Titulo VARCHAR(100),
    Editorial VARCHAR(50),
    Area VARCHAR(50),
    PRIMARY KEY (IdLibro)
);

CREATE TABLE Autor(
    IdAutor INT NOT NULL,
    Nombre VARCHAR(50),
    Nacionalidad VARCHAR(50),
    PRIMARY KEY(IdAutor)
);

CREATE TABLE Estudiante(
    IdLector INT NOT NULL,
    Nombre VARCHAR(50),
    Direccion VARCHAR(50),
    Carrera VARCHAR(50),
    Edad INT,
    PRIMARY KEY(IdLector)
);

CREATE TABLE LibAut(
    IdAutor INT NOT NULL,
    IdLibro INT NOT NULL,
    FOREIGN KEY(IdAutor) REFERENCES Autor(IdAutor),
    FOREIGN KEY(IdLibro) REFERENCES Libro(IdLibro)
);

CREATE TABLE Prestamo(
    IdLector INT NOT NULL,
    IdLibro INT NOT NULL,
    FechaPrestamo date,
    FechaDevolucion date,
    devuelto VARCHAR(15),
    FOREIGN KEY(IdLector) REFERENCES Estudiante(IdLector),
    FOREIGN KEY(IdLibro) REFERENCES Libro(IdLibro)
);

INSERT INTO Libro (IdLibro, Titulo, Editorial, Area) VALUES
(01, 'Caperucita', 'Noriega', 'Español'),
(02, 'Los 3 cochinitos', 'Arlequin', 'Español'),
(03, 'Algebra', 'Arlequin', 'Matematicas'),
(04, 'Matematicas 2', 'Arlequin', 'Matematicas'),
(05, 'Informatica II', 'Arlequin', 'Informatica');

SELECT * FROM Libro;

INSERT INTO Autor (IdAutor, Nombre, Nacionalidad) VALUES
(01, 'Alejandro Escamilla', 'Argentino'),
(02, 'Fernando Altamirar', 'Mexicano'),
(03, 'Cesar Orozco', 'Brasileño'),
(04, 'Pedro Almendaris', 'Cubano'),
(05, 'Pedro Cazares', 'Argentino');

SELECT * FROM Autor;

INSERT INTO Estudiante (IdLector, Nombre, Direccion, Carrera, Edad) VALUES
(01, 'Alejandro Mendoza', 'Chiquimula', 'Informatica', 18),
(02, 'Fernando mendoza', 'Peten', 'informatica', 18),
(03, 'Ceterina Figueroa', 'Coban', 'Contaduria', 20),
(04, 'Ivonne Ramirez', 'Coban', 'Psicologia', 19),
(05, 'Jairo Villanueva', 'El Progreso', 'Informatica', 19);

SELECT * FROM Estudiante;

INSERT INTO LibAut (IdAutor, IdLibro) VALUES
(01, 01),
(02, 02),
(03, 03),
(04, 04),
(05, 05);

SELECT * FROM LibAut;

INSERT INTO Prestamo (IdLector, IdLibro, FechaPrestamo, FechaDevolucion, devuelto) VALUES
(01, 01, '2023-08-06','2023-09-06','no'),
(02, 02,'2023-08-13','2023-09-06','no'),
(03, 03,'2023-09-06','2023-11-06','si'),
(04, 04,'2023-11-06','2023-11-06','si'),
(05, 05,'2023-08-08','2023-09-29','no');

SELECT * FROM Prestamo;

CREATE VIEW VistaSimple1 AS SELECT Nombre, Edad FROM Estudiante;

SELECT * FROM VistaSimple1;

show create view VistaSimple1;

CREATE VIEW Vista1 AS 
SELECT Libro.IdLibro, Titulo, Editorial 
FROM Libro
INNER JOIN Prestamo
ON Libro.IdLibro = Prestamo.IdLibro;

select * from Vista1;

CREATE INDEX I_Libro_Titulo 
ON Libro(Titulo);

Show index from Libro;