d3.select(".time-chart")
  .selectAll("div")
    .data({"serial": 0.000838216, "parallel": 0.00812971})
  .enter().append("div")
    .style("width", function(d) { return d * 10 + "px"; })
    .text(function(d) { return d; });
