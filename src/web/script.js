var dataStr = "";
var data = {};

// helper function: log message to screen
function log(msg) {
    document.getElementById('log').textContent += msg + '\n';
}

// setup websocket with callbacks
var ws = new WebSocket('ws://localhost:8080/');
ws.onopen = function() {
    log('CONNECT');
};
ws.onclose = function() {
    data = JSON.parse(dataStr);
    /*console.log(JSON.stringify(data));*/
    drawGraphs(data);
    log('DISCONNECT');
};
ws.onmessage = function(event) {
    dataStr += event.data;
    log('MESSAGE: ' + event.data);
};

/*var some_data = {
    "nodes": [{
        "id": 1
    }, {
        "id": 2
    }, {
        "id": 3
    }],
    "edges": [{
        "source": 1,
        "target": 2
    }, {
        "source": 1,
        "target": 3,
    }]
};
alchemy.begin({
    "dataSource": some_data
})
*/

function drawGraphs(data) {
    //time bar graph comparison
    var ctx = document.getElementById("time-bar-chart");
    var myChart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: ["Serial", "Parallel"],
            datasets: [{
                label: '# of Seconds For K-Means',
                data: [data.kmeans.serial.time, data.kmeans.parallel.time],
                backgroundColor: [
                    'rgba(255, 99, 132, 0.2)',
                    'rgba(54, 162, 235, 0.2)'
                ],
                borderColor: [
                    'rgba(255,99,132,1)',
                    'rgba(54, 162, 235, 1)'
                ],
                borderWidth: 1
            }]
        },
        options: {
            scales: {
                yAxes: [{
                    ticks: {
                        beginAtZero: true
                    }
                }]
            }
        }
    });
}
