const net = require('net');
const readline = require('readline');
const fs = require('fs');
const path = require('path');

const client = new net.Socket();
const PORT = 3000;
const HOST = '127.0.0.1';
const clientFolderPath = path.join(__dirname, 'client');

client.connect(PORT, HOST, () => {
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.prompt();

    rl.on('line', (input) => {
        if (input === 'ls') {
            listServerFiles();
        } else if (input.startsWith('upload')) {
            const fileUpload = input.substring(input.indexOf(' ') + 1);
            uploadFile(fileUpload);
        } else if (input.startsWith('download')) {
            const fileDownload = input.substring(input.indexOf(' ') + 1);
            downloadFile(fileDownload);
        } else {
            client.write(input + '\r\n');
        }
        rl.prompt();
    });

    client.on('data', (data) => {
        console.log(data.toString());
    });

    client.on('close', () => {
        console.log('Connection closed');
        rl.close();
    });

    const listServerFiles = () => {
        client.write('ls\r\n');
    };

    const uploadFile = (fileName) => {
        try {
            const filePath = path.join(clientFolderPath, fileName);
            const fileData = fs.readFileSync(filePath);
            client.write(`upload ${fileName} ${fileData.toString('binary')}`);
        } catch (err) {
            console.log("File not found");
        }
    };

    const downloadFile = (fileName) => {
        client.write(`download ${fileName}\r\n`);
    };
});
