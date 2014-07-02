var displaydata = (function () {
	console.log("inside displaydata")
	var totalPoints = 1000;
	var resX = [];
	var resY = [];
	var plot;
	getInitData = function () {
		// zip the generated y values with the x values
		for (var i = 0; i < totalPoints; ++i) {
			resX.push([i, 0]);
			resY.push([i, 0]);
		}
		return [resX, resY];
	}
	// Options for Flot plot
	var options = {
		series : {
			shadowSize : 0
		}, // drawing is faster without shadows
		yaxis : {
			min : -180,
			max : 180
		},
		xaxis : {
			show : false
		}
	};

	// Update the JQuery UI Progress Bar
	init = function () {
		plot = $.plot($("#placeholder"), getInitData(), options);
		$("#progressbar").progressbar({
			value : 0
		});
	}
	updatedisplay = function (valX, valY) {
		// Put sensor value to the 'sensor_value' span
		$('#sensor_value').html(valX);

		// Push new value to Flot Plot
		resX.push([totalPoints, valX]); // push on the end side
		resX.shift(); // remove first value to maintain 300 points
		resY.push([totalPoints, valY]); // push on the end side
		resY.shift(); // remove first value to maintain 300 points
		// reinitialize the x axis data points to 0 to 299.
		for (i = 0; i < totalPoints; i++) {
			resX[i][0] = i;
			resY[i][0] = i;
		}
		// Redraw the plot
		plot.setData([resX, resY]);
		plot.draw();

		// Update JQuery UI progress bar.
		$("#progressbar").progressbar({
			value : valX
		});

	}
	return {
		init : init,
		updatedisplay : updatedisplay
	}
})();
