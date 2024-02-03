const net = require('net');

const startTime = new Date();

const server = net.createServer((socket) => {
    console.log('Client connected');

    socket.write(`You connect to server\r\n`);
    socket.write(`Current time: ${startTime.toLocaleTimeString()}\r\n`);

    function getUptime() {
        const currentTime = new Date();
        const uptimeMilliseconds = currentTime - startTime;
        return `${uptimeMilliseconds / 1000}s`;
    } 

    socket.on('data', (data) => {
        const arg = data.toString().trim();

        const command = arg.toString().substring(0, arg.indexOf(' '));

        if(command && command === "echo" || command === "ECHO"){ 
            socket.write(`Echo:${arg.toString().substring(arg.indexOf(' ') + 1)}\r\n`);
        }else {
            switch (arg) {
                case 'time':
                case 'TIME':
                    const uptime = getUptime();
                    socket.write(`Uptime: ${uptime}\r\n`);
                    break;
                case 'CLOSE':
                case 'EXIT':
                case 'QUIT':
                    socket.write('Goodbye!\r\n');
                    socket.end();
                    break;
                default:
                    socket.write('Unknown command\r\n');
            }
        }
    });

    socket.on('end', () => {
        console.log('Client disconnected');
    });
});

const PORT = 3000;
server.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
