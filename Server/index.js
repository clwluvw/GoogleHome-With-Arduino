const express = require('express')
const webSocket = require('ws')
const app = express()
const port = 8010
const wsPort = 8011
const wss = new webSocket.Server({ port: wsPort });

var data = "";

app.get('/config', (req, res) => {
	console.log(req.query);
	if(req.query.lampID === '1' || req.query.lampID === 'one') {
		data = "lampID: 1";
		res.send('lampOne detected')
		if (req.query.state === '0' || req.query.state === 'off') {
			data += ", state: 0";
			console.log('lampOne Off')
		}
		else if (req.query.state === '1' || req.query.state === 'on') {
			data += ", state: 1";
			console.log('lampOne On')
		}
		console.log(data)
		wss.clients.forEach(function each(ws) {
			if (ws.isAlive == false)
				return ws.terminate();
			ws.send(data);
		});
	}
})

app.listen(port, () => console.log('listening...'))

wss.on('connection', function connection(ws) {
	console.log('client connected');
	ws.on('message', function incoming(message) {
		console.log((new Date()) + 'received: %s', message);
	});

	ws.send('connected');
});


