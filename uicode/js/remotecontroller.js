var remotecontroller = (function () {
	var controllerValue;
	var $theDragger;
	var initialValue =  {x:0,y:0};
	var contollerValue =  {x:0,y:0};
	init = function () {
		$(function() {
			$theDragger = $( "#draggable" )
			$('#dragX').html(0);
			$('#dragY').html(0);
			$theDragger.draggable({ revert: true,
				start: function() {
					updateInitialValue();
				  },
				drag: function() {
					updateControllerValue();
				},
				stop: function() {
					resetControllerValue();
				},
			});
		});
	}
	updateInitialValue = function () {
		initialValue.x = $theDragger.position().left;
		initialValue.y = $theDragger.position().top;
	}
	updateControllerValue = function () {
		contollerValue.x = $theDragger.position().left - initialValue.x;
		contollerValue.y = initialValue.y - $theDragger.position().top;
		$('#dragX').html(contollerValue.x);
		$('#dragY').html(contollerValue.y);
		$('#dragY').trigger( "contollerValueEvent", [contollerValue] );
	}
	resetControllerValue = function () {
		contollerValue.x = 0;
		contollerValue.y = 0;
		$('#dragX').html(0);
		$('#dragY').html(0);
		$('#dragY').trigger( "contollerValueEvent", [contollerValue] );
	}
	getControllerValue = function () {
		return controllerValue;
	}
	return {
		getControllerValue : getupdateButton,
		init : init
	}
})();
