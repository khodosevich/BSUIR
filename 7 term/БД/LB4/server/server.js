const express = require('express');
const mongoose = require('mongoose');

const app = express();
const port = 3001;

mongoose.connect('mongodb://localhost:27017/semester7', {
  useNewUrlParser: true,
  useUnifiedTopology: true
})
    .then(() => {
      console.log('Подключение к MongoDB успешно');
      app.listen(port, () => console.log('Server is running on port 3001'));
    })
    .catch(err => console.error('Ошибка подключения к MongoDB:', err));

const clientsSchema = new mongoose.Schema({
  id: Number,
  full_name: String,
  passport: String,
  phone: String
});

const filmsSchema = new mongoose.Schema({
  id: Number,
  name: String,
  year: String,
  genre: String
});

const orderSchema = new mongoose.Schema({
  id: Number,
  time_get: Number,
  order_time: String,
  time_out: String,
  sum: Number,
  client_id: Number
});

const disksSchema = new mongoose.Schema({
  id: Number,
  rental_cost: Number,
  quantity: Number,
  state: String
});

const Films = mongoose.model('Films', filmsSchema);
const Clients = mongoose.model('Clients', clientsSchema);
const Disks = mongoose.model('Disks', orderSchema);
const Orders = mongoose.model('Orders', disksSchema);

console.log(Orders);

app.use(express.json());

app.get('/', (req, res) => {
  res.send('Сервер работает успешно');
});

app.get('/film', async (req, res) => {
  try {
    const films = await Films.find({});
    res.json(films);
  } catch (err) {
    console.error(err);
    res.status(500).send('Ошибка сервера');
  }
});

app.get('/client', async (req, res) => {
  try {
    console.log("hello");
    const client = await Clients.find({});
    console.log(client);
    res.json(client);
  } catch (err) {
    console.error(err);
    res.status(500).send('Ошибка сервера');
  }
});

app.get('/orders', async (req, res) => {
  try {
    const orders = await Orders.find({});
    res.json(orders);
  } catch (err) {
    console.error(err);
    res.status(500).send('Ошибка сервера');
  }
});

app.get('/disk', async (req, res) => {
  try {
    const disk = await Disks.find({});
    res.json(disk);
  } catch (err) {
    console.error(err);
    res.status(500).send('Ошибка сервера');
  }
});

app.post('/query', async (req, res) => {
  const { collection, action, data, query } = req.body;

  try {
    const dbCollection = mongoose.connection.collection(collection);

    let result;

    switch (action) {
      case 'insert':
        result = await dbCollection.insertOne(data);
        res.json({ success: true, result });
        break;

      case 'delete':
        result = await dbCollection.deleteOne(query);
        res.json({ success: true, result });
        break;

      case 'query':
        result = await dbCollection.find(query).toArray();
        res.json(result);
        break;

      default:
        res.status(400).json({ error: "Invalid action type" });
    }
  } catch (err) {
    console.error("Error during operation:", err);
    res.status(500).json({ error: 'Server error' });
  }
});
