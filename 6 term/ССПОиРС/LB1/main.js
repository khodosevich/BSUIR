const net = require('net');
const fs = require('fs');
const path = require('path');

const startTime = new Date();
const serverFolderPath = path.join(__dirname, 'server');

const server = net.createServer((socket) => {
    console.log('Client connected');

    socket.write(`You are connected to the server\r\n`);
    socket.write(`Current time: ${startTime.toLocaleTimeString()}\r\n`);

    socket.on('data', (data) => {
        const arg = data.toString().trim();

        if (arg.indexOf(' ') === -1) {
            switch (arg) {
                case 'time':
                    sendUptime();
                    break;
                case 'ls':
                    listFiles(socket);
                    break;
                case 'close':
                case 'exit':
                case 'quit':
                    closeConnection();
                    break;
                default:
                    socket.write(`Error: Invalid command\r\n`);
                    break;
            }
        } else {
            const command = arg.substring(0, arg.indexOf(' '));
            switch (command) {
                case 'echo':
                    socket.write(`${arg.toString().substring(arg.indexOf(' ') + 1)}\r\n`);
                    break;
                case 'upload':
                    receiveFile(arg, socket);
                    break;
                case 'download':
                    sendFile(arg, socket);
                    break;
                default:
                    socket.write(`Error: Invalid command\r\n`);
                    break;
            }
        }
    });

    socket.on('end', () => {
        console.log('Client disconnected');
    });

    const sendUptime = () => {
        const uptime = getUptime();
        socket.write(`Uptime: ${uptime}\r\n`);
    };

    const getUptime = () => {
        const currentTime = new Date();
        const uptimeMilliseconds = currentTime - startTime;
        return `${uptimeMilliseconds / 1000}s`;
    };

    const closeConnection = () => {
        socket.write('Goodbye!\r\n');
        socket.end();
    };

    const listFiles = (socket) => {
        socket.write("Files in server folder: ");
        const files = fs.readdirSync(serverFolderPath);
        files.forEach(file => {
            socket.write(`${file}\r\n`);
        });
    };

    const receiveFile = (arg, socket) => {
        const fileParts = arg.split(' ');
        const fileName = fileParts[1];
        const fileData = Buffer.from(fileParts.slice(2).join(' '), 'binary');

        fs.writeFile(path.join(serverFolderPath, fileName), fileData, (err) => {
            if (err) throw err;
            console.log('The file has been saved!\n');
            socket.write(`File ${fileName} has been uploaded successfully\r\n`);
        });
    };

    const sendFile = (arg, socket) => {
        const fileParts = arg.split(' ');
        const fileName = fileParts[1];
        const filePath = path.join(serverFolderPath, fileName);

        fs.readFile(filePath, (err, fileData) => {
            if (err) {
                socket.write(`Error reading file: ${err.message}\r\n`);
            } else {
                socket.write(`FILE ${fileName} ${fileData.length}\r\n`);
                socket.write(fileData);
            }
        });
    };
});

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
