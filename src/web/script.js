function loadScript(url, callback) {
    // Adding the script tag to the head as suggested before
    var head = document.getElementsByTagName('head')[0];
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;

    // Then bind the event to the callback function.
    // There are several events for cross browser compatibility.
    script.onreadystatechange = callback;
    script.onload = callback;

    // Fire the loading
    head.appendChild(script);
}

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
    log('DISCONNECT');
};
ws.onmessage = function(event) {
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
