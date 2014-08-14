var displaydata = (function () {
	console.log("inside displaydata")
	var totalPoints = 1000;
	var resX = [];
	var resY = [];
	var calibrateButton;
	getInitData = function () {
		// zip the generated y values with the x values
		for (var i = 0; i < totalPoints; ++i) {
			resX.push([i, 0]);
			resY.push([i, 0]);
		}
		return [resX, resY];
	}

	init = function () {
		calibrateButton = $("#docalibrate")
	}
	getcalibrateButton = function () {
		return calibrateButton;
	}
	return {
		init : init,
		calibrateButton : getcalibrateButton
	}
})();
