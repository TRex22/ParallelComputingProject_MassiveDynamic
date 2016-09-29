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


function drawGraphs(data) {
    highChartTheme();
    data = convertToNumbers(data);

    drawTimeBarGraph(data);
    drawErrorBarGraph(data);
    drawScatterPlot(data);
}

function getPlotDimension3D(data) {
    if (data.kmeans.serial.data[0].length === 2) {
        return false;
    } else if (data.kmeans.serial.data[0].length === 3) {
        return true;
    }
    return false;
}

function convertToNumbers(data) {
    data.kmeans.serial.data = convertStrArrayToFloat(data.kmeans.serial.data);
    data.kmeans.parallel.data = convertStrArrayToFloat(data.kmeans.parallel.data);

    data.kmeans.serial.minX = findDataMinX(data.kmeans.serial.data) - 2;
    data.kmeans.serial.minY = findDataMinY(data.kmeans.serial.data) - 2;
    data.kmeans.serial.minZ = findDataMinZ(data.kmeans.serial.data) - 2;

    data.kmeans.serial.maxX = findDataMaxX(data.kmeans.serial.data) + 2;
    data.kmeans.serial.maxY = findDataMaxY(data.kmeans.serial.data) + 2;
    data.kmeans.serial.maxZ = findDataMaxZ(data.kmeans.serial.data) + 2;

    data.kmeans.parallel.minX = findDataMinX(data.kmeans.parallel.data) - 2;
    data.kmeans.parallel.minY = findDataMinY(data.kmeans.parallel.data) - 2;
    data.kmeans.parallel.minZ = findDataMinZ(data.kmeans.parallel.data) - 2;

    data.kmeans.parallel.maxX = findDataMaxX(data.kmeans.parallel.data) + 2;
    data.kmeans.parallel.maxY = findDataMaxY(data.kmeans.parallel.data) + 2;
    data.kmeans.parallel.maxZ = findDataMaxZ(data.kmeans.parallel.data) + 2;

    return data;
}

function findDataMinX(dataArr) {
    var minx = null;
    for (var i = 0; i < dataArr.length; i++) {
        if (minx === null) {
            minx = dataArr[i][0];
        } else if (minx > dataArr[i][0]) {
            minx = dataArr[i][0];
        }
    }

    return minx;
}

function findDataMinY(dataArr) {
    var miny = null;
    for (var i = 0; i < dataArr.length; i++) {
        if (miny === null) {
            miny = dataArr[i][1];
        } else if (miny > dataArr[i][1]) {
            miny = dataArr[i][1];
        }
    }

    return miny;
}

function findDataMinZ(dataArr) {
    var minz = null;

    if (dataArr[0].length === 3) {
        for (var i = 0; i < dataArr.length; i++) {
            if (minz === null) {
                minz = dataArr[i][2];
            } else if (minz > dataArr[i][2]) {
                minz = dataArr[i][2];
            }
        }
    }

    return minz;
}

function findDataMaxX(dataArr) {
    var maxx = null;

    for (var i = 0; i < dataArr.length; i++) {
        if (maxx === null) {
            maxx = dataArr[i][0];
        } else if (maxx < dataArr[i][0]) {
            maxx = dataArr[i][0];
        }
    }

    return maxx;
}

function findDataMaxY(dataArr) {
    var maxy = null;

    for (var i = 0; i < dataArr.length; i++) {
        if (maxy === null) {
            maxy = dataArr[i][1];
        } else if (maxy < dataArr[i][1]) {
            maxy = dataArr[i][1];
        }
    }

    return maxy;
}

function findDataMaxZ(dataArr) {
    var maxz = null;

    if (dataArr[0].length === 3) {
        for (var i = 0; i < dataArr.length; i++) {
            if (maxz === null) {
                maxz = dataArr[i][2];
            } else if (maxz < dataArr[i][2]) {
                maxz = dataArr[i][2];
            }
        }
    }

    return maxz;
}

function convertStrArrayToFloat(arr) {
    var floatArr = [];

    if (arr[0].length === 2) {
        for (var i = 0; i < arr.length; i++) {
            var dataPoint = [parseFloat(arr[i][0]), parseFloat(arr[i][1])];
            floatArr.push(dataPoint);
        }
    } else if (arr[0].length === 3) {
        for (var i = 0; i < arr.length; i++) {
            var dataPoint = [parseFloat(arr[i][0]), parseFloat(arr[i][1]), parseFloat(arr[i][2])];
            floatArr.push(dataPoint);
        }
    }

    return floatArr;
}

function drawTimeBarGraph(data) {
    //time bar graph comparison
    var ctx = document.getElementById("time-chart");

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

function drawErrorBarGraph(data) {
    //time bar graph comparison
    var ctx = document.getElementById("error-chart");
    var myChart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: ["Serial", "Parallel"],
            datasets: [{
                label: '# Mean Squared Error For K-Means',
                data: [data.kmeans.serial.error, data.kmeans.parallel.error],
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

function drawScatterPlot(data) {
    var is3D = getPlotDimension3D(data);

    $(function() {
        // Give the points a 3D feel by adding a radial gradient
        Highcharts.getOptions().colors = $.map(Highcharts.getOptions().colors, function(color) {
            return {
                radialGradient: {
                    cx: 0.4,
                    cy: 0.3,
                    r: 0.5
                },
                stops: [
                    [0, color],
                    [1, Highcharts.Color(color).brighten(-0.2).get('rgb')]
                ]
            };
        });

        // Set up the chart
        var chart = new Highcharts.Chart({
            chart: {
                renderTo: 'scatter-chart-data',
                margin: 100,
                type: 'scatter',
                options3d: {
                    enabled: is3D,
                    alpha: 10,
                    beta: 30,
                    depth: 250,
                    viewDistance: 5,
                    fitToPlot: false,
                    frame: {
                        bottom: { size: 1, color: 'rgba(0,0,0,0.02)' },
                        back: { size: 1, color: 'rgba(0,0,0,0.04)' },
                        side: { size: 1, color: 'rgba(0,0,0,0.06)' }
                    }
                }
            },
            title: {
                text: 'Initial Data Points'
            },
            subtitle: {
                text: 'Not Yet Clustered But Normalized'
            },
            plotOptions: {
                scatter: {
                    width: 10,
                    height: 10,
                    depth: 10
                }
            },
            yAxis: {
                min: data.kmeans.serial.minY,
                max: data.kmeans.serial.maxY,
                title: null
            },
            xAxis: {
                min: data.kmeans.serial.minX,
                max: data.kmeans.serial.maxX,
                gridLineWidth: 1
            },
            zAxis: {
                min: data.kmeans.serial.minZ,
                max: data.kmeans.serial.maxZ,
                showFirstLabel: false
            },
            legend: {
                enabled: false
            },
            series: [{
                name: 'Initial Data But Normalized',
                colorByPoint: true,
                data: data.kmeans.serial.data
            }]
        });

        // Add mouse events for rotation
        $(chart.container).bind('mousedown.hc touchstart.hc', function(eStart) {
            eStart = chart.pointer.normalize(eStart);

            var posX = eStart.pageX,
                posY = eStart.pageY,
                alpha = chart.options.chart.options3d.alpha,
                beta = chart.options.chart.options3d.beta,
                newAlpha,
                newBeta,
                sensitivity = 5; // lower is more sensitive

            $(document).bind({
                'mousemove.hc touchdrag.hc': function(e) {
                    // Run beta
                    newBeta = beta + (posX - e.pageX) / sensitivity;
                    chart.options.chart.options3d.beta = newBeta;

                    // Run alpha
                    newAlpha = alpha + (e.pageY - posY) / sensitivity;
                    chart.options.chart.options3d.alpha = newAlpha;

                    chart.redraw(false);
                },
                'mouseup touchend': function() {
                    $(document).unbind('.hc');
                }
            });
        });

    });
}

function highChartTheme() {
    /**
     * Dark theme for Highcharts JS
     * @author Torstein Honsi
     */

    // Load the fonts
    Highcharts.createElement('link', {
        href: 'https://fonts.googleapis.com/css?family=Unica+One',
        rel: 'stylesheet',
        type: 'text/css'
    }, null, document.getElementsByTagName('head')[0]);

    Highcharts.theme = {
        colors: ["#2b908f", "#90ee7e", "#f45b5b", "#7798BF", "#aaeeee", "#ff0066", "#eeaaee",
            "#55BF3B", "#DF5353", "#7798BF", "#aaeeee"
        ],
        chart: {
            backgroundColor: {
                linearGradient: { x1: 0, y1: 0, x2: 1, y2: 1 },
                stops: [
                    [0, '#2a2a2b'],
                    [1, '#3e3e40']
                ]
            },
            style: {
                fontFamily: "'Unica One', sans-serif"
            },
            plotBorderColor: '#606063'
        },
        title: {
            style: {
                color: '#E0E0E3',
                textTransform: 'uppercase',
                fontSize: '20px'
            }
        },
        subtitle: {
            style: {
                color: '#E0E0E3',
                textTransform: 'uppercase'
            }
        },
        xAxis: {
            gridLineColor: '#707073',
            labels: {
                style: {
                    color: '#E0E0E3'
                }
            },
            lineColor: '#707073',
            minorGridLineColor: '#505053',
            tickColor: '#707073',
            title: {
                style: {
                    color: '#A0A0A3'

                }
            }
        },
        yAxis: {
            gridLineColor: '#707073',
            labels: {
                style: {
                    color: '#E0E0E3'
                }
            },
            lineColor: '#707073',
            minorGridLineColor: '#505053',
            tickColor: '#707073',
            tickWidth: 1,
            title: {
                style: {
                    color: '#A0A0A3'
                }
            }
        },
        tooltip: {
            backgroundColor: 'rgba(0, 0, 0, 0.85)',
            style: {
                color: '#F0F0F0'
            }
        },
        plotOptions: {
            series: {
                dataLabels: {
                    color: '#B0B0B3'
                },
                marker: {
                    lineColor: '#333'
                }
            },
            boxplot: {
                fillColor: '#505053'
            },
            candlestick: {
                lineColor: 'white'
            },
            errorbar: {
                color: 'white'
            }
        },
        legend: {
            itemStyle: {
                color: '#E0E0E3'
            },
            itemHoverStyle: {
                color: '#FFF'
            },
            itemHiddenStyle: {
                color: '#606063'
            }
        },
        credits: {
            style: {
                color: '#666'
            }
        },
        labels: {
            style: {
                color: '#707073'
            }
        },

        drilldown: {
            activeAxisLabelStyle: {
                color: '#F0F0F3'
            },
            activeDataLabelStyle: {
                color: '#F0F0F3'
            }
        },

        navigation: {
            buttonOptions: {
                symbolStroke: '#DDDDDD',
                theme: {
                    fill: '#505053'
                }
            }
        },

        // scroll charts
        rangeSelector: {
            buttonTheme: {
                fill: '#505053',
                stroke: '#000000',
                style: {
                    color: '#CCC'
                },
                states: {
                    hover: {
                        fill: '#707073',
                        stroke: '#000000',
                        style: {
                            color: 'white'
                        }
                    },
                    select: {
                        fill: '#000003',
                        stroke: '#000000',
                        style: {
                            color: 'white'
                        }
                    }
                }
            },
            inputBoxBorderColor: '#505053',
            inputStyle: {
                backgroundColor: '#333',
                color: 'silver'
            },
            labelStyle: {
                color: 'silver'
            }
        },

        navigator: {
            handles: {
                backgroundColor: '#666',
                borderColor: '#AAA'
            },
            outlineColor: '#CCC',
            maskFill: 'rgba(255,255,255,0.1)',
            series: {
                color: '#7798BF',
                lineColor: '#A6C7ED'
            },
            xAxis: {
                gridLineColor: '#505053'
            }
        },

        scrollbar: {
            barBackgroundColor: '#808083',
            barBorderColor: '#808083',
            buttonArrowColor: '#CCC',
            buttonBackgroundColor: '#606063',
            buttonBorderColor: '#606063',
            rifleColor: '#FFF',
            trackBackgroundColor: '#404043',
            trackBorderColor: '#404043'
        },

        // special colors for some of the
        legendBackgroundColor: 'rgba(0, 0, 0, 0.5)',
        background2: '#505053',
        dataLabelsColor: '#B0B0B3',
        textColor: '#C0C0C0',
        contrastTextColor: '#F0F0F3',
        maskColor: 'rgba(255,255,255,0.3)'
    };

    // Apply the theme
    Highcharts.setOptions(Highcharts.theme);
}
