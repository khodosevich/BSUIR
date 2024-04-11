const express = require('express');
const { Pool } = require('pg');

const app = express();
const port = 3001;

const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'prokat_disks',
  password: '',
  port: 5433,
});

app.use(express.json());

app.get('/', (req, res) => {
  res.send('Сервер работает успешно');
});

const getTableData = async (req, res, table) => {
  try {
    const client = await pool.connect();
    const result = await client.query(`SELECT * FROM ${table}`);
    const data = result.rows;
    res.json(data);
    client.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
};

app.get('/client', async (req, res) => {
  await getTableData(req, res, 'client');
});

app.get('/disks', async (req, res) => {
  await getTableData(req, res, 'disk');
});

app.get('/film', async (req, res) => {
  await getTableData(req, res, 'film');
});

app.get('/reviews', async (req, res) => {
  await getTableData(req, res, 'review');
});

app.get('/orders', async (req, res) => {
  await getTableData(req, res, '"order"');
});

app.get('/query', async (req, res) => {
  const { query } = req.query;
  try {
    const result = await pool.query(query);
    res.json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/like', async (req, res) => {
  try {
    const like = await pool.connect();
    const result = await like.query('SELECT full_name,phone FROM client WHERE full_name LIKE \'%Kho%\'');
    const films = result.rows;
    res.json(films);
    like.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/genre', async (req, res) => {
  try {
    const genre = await pool.connect();
    const result = await genre.query('SELECT name,year,genre\n' +
        'FROM film WHERE year > \'2000-01-01\' AND genre = \'боевик\'');
    const films = result.rows;
    res.json(films);
    genre.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/client-order', async (req, res) => {
  try {
    const client = await pool.connect();
    const result = await client.query('SELECT client.full_name, "order".sum, "order".time_get, "order".time_out\n' +
        'FROM client\n' +
        'INNER JOIN "order" ON client.id = "order".client_id\n' +
        'WHERE "order".sum > 10 AND "order".sum < 30 ');
    const films = result.rows;
    res.json(films);
    client.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/order-sum', async (req, res) => {
  try {
    const orderSum = await pool.connect();
    const result = await orderSum.query('SELECT SUM(sum) AS total_sum FROM "order"');
    const films = result.rows;
    res.json(films);
    orderSum.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/avg', async (req, res) => {
  try {
    const avg = await pool.connect();
    const result = await avg.query('SELECT AVG(rental_cost) AS average_cost FROM disk');
    const films = result.rows;
    res.json(films);
    avg.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.get('/client-count', async (req, res) => {
  try {
    const clientCount = await pool.connect();
    const result = await clientCount.query('SELECT COUNT(id) AS client_count from client;');
    const films = result.rows;
    res.json(films);
    clientCount.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}`);
});