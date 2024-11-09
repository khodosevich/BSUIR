const { Pool } = require('pg');
const { MongoClient } = require('mongodb');
const express = require('express');

const app = express();
const port = 3001;

const pool = new Pool({
  user: "postgres",
  host: "localhost",
  database: "semestr7",
  password: "", //свой пароль
  port: "", //свой порт
});

// Настройки MongoDB
const mongoClient = new MongoClient("mongodb://localhost:27017");
let mongoDb;

// Функция переноса данных из PostgreSQL в MongoDB с проверкой на наличие данных
async function transferData(table, collectionName) {
  try {
    const client = await pool.connect();
    const result = await client.query(`SELECT * FROM ${table}`);
    const rows = result.rows;

    if (rows.length === 0) {
      console.log(`Таблица ${table} пуста. Пропускаем.`);
      return;
    }

    const collection = mongoDb.collection(collectionName);
    await collection.deleteMany({}); // Очищаем коллекцию
    await collection.insertMany(rows); // Вставляем данные

    console.log(`Успешно перенесли данные из таблицы ${table} в коллекцию ${collectionName}`);
    client.release();
  } catch (err) {
    console.error(`Ошибка при переносе данных из ${table}:`, err);
  }
}

// Основная функция конвертации
async function convertPostgresToMongo() {
  try {
    await mongoClient.connect();
    mongoDb = mongoClient.db('semester7');

    // Перенос таблиц
    await transferData('client', 'clients');
    await transferData('disk', 'disks');
    await transferData('film', 'films');
    await transferData('"order"', 'orders');

    console.log('Конвертация завершена.');
  } catch (error) {
    console.error('Ошибка при конвертации:', error);
  } finally {
    await pool.end();
    await mongoClient.close();
  }
}

// Маршрут для запуска конвертации по запросу
app.get('/convert', async (req, res) => {
  try {
    await convertPostgresToMongo();
    res.send('Конвертация завершена успешно');
  } catch (err) {
    res.status(500).send('Ошибка при конвертации');
  }
});

// Запуск сервера
app.listen(port, () => {
  console.log(`Сервер запущен на http://localhost:${port}`);
});