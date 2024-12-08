CREATE DATABASE kontaktbok;

USE kontaktbok;

CREATE TABLE contacts (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE emails (
    id INT AUTO_INCREMENT PRIMARY KEY,
    contact_id INT NOT NULL,
    email VARCHAR(100) NOT NULL,
    FOREIGN KEY (contact_id) REFERENCES contacts(id) ON DELETE CASCADE
);

CREATE TABLE phone_numbers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    contact_id INT NOT NULL,
    phone_number VARCHAR(20) NOT NULL,
    FOREIGN KEY (contact_id) REFERENCES contacts(id) ON DELETE CASCADE
);