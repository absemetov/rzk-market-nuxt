const app = require('./app');
const bot = require('./bot');

exports.app = app.app;
exports.bot = bot.bot;


//test ssr
// const express = require('express');
// const app = express();
// const engines = require("consolidate");

// app.engine('hbs', engines.handlebars);
// app.set('views', './views');
// app.set('view engine', 'hbs');

// app.get('/', async (request, response) => {
//   const currencies = await admin.firestore().collection('currencies').get();
//   response.render('index', {currencies: currencies.docs.map(doc => [doc.id, doc.data()])});
// });

// app.get('/timestamp', (request, response) => {
//   response.send(`${Date.now()}`);
// });

// app.get('/timestamp-cached', (request, response) => {
//   response.set('Cache-Control', 'public, max-age=300, s-maxage=600');
//   response.send(`${Date.now()}`);
// });


// //exports.app = functions.https.onRequest(app);












