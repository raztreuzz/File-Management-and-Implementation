-- Insertar datos en la tabla Clientes
INSERT INTO Clientes (nombre, telefono) VALUES
('Juan Pérez', '555-1234'),
('María López', '555-5678'),
('Carlos González', '555-8765'),
('Ana Rodríguez', '555-4321');

-- Insertar datos en la tabla Productos
INSERT INTO Productos (nombre, precio, cantidad) VALUES
('Paracetamol', 1.50, 100),
('Ibuprofeno', 2.00, 200),
('Aspirina', 1.75, 150),
('Jarabe para la tos', 3.50, 50);

-- Insertar datos en la tabla Ventas
INSERT INTO Ventas (id_cliente, fecha) VALUES
(1, '2024-10-10'),
(2, '2024-10-11'),
(3, '2024-10-12'),
(4, '2024-10-13');

-- Insertar datos en la tabla Detalles_Venta
INSERT INTO Detalles_Venta (id_venta, id_producto, cantidad) VALUES
(1, 1, 5), -- Juan compró 5 Paracetamol
(1, 2, 3), -- Juan compró 3 Ibuprofeno
(2, 3, 2), -- María compró 2 Aspirina
(2, 4, 1), -- María compró 1 Jarabe para la tos
(3, 1, 10), -- Carlos compró 10 Paracetamol
(4, 2, 4), -- Ana compró 4 Ibuprofeno
(4, 3, 6); -- Ana compró 6 Aspirina

