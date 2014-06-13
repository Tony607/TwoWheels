var TheCube = function () {
	this.camera,
	this.scene,
	this.renderer;
	this.geometry;
	var x = 0;
	var y = 0;

	var material;
	var cube;
	var angle = 0;
	function init() {
		var canvasWidth = 846;
		var canvasHeight = 494;
		this.renderer = new THREE.WebGLRenderer();
		this.renderer.setSize(window.innerWidth / 2, window.innerHeight / 2);

		this.camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 1, 1000);
		this.camera.position.z = 5;
	}

	function fillScene() {
		this.scene = new THREE.Scene();

		// LIGHTS
		this.scene.add(new THREE.AmbientLight(0x222222));

		headlight = new THREE.PointLight(0xFFFFFF, 1.0);
		this.scene.add(headlight);

		var light = new THREE.SpotLight(0xFFFFFF, 1.0);
		light.position.set(-600, 1200, 300);
		light.angle = 20 * Math.PI / 180;
		light.exponent = 1;
		light.target.position.set(0, 200, 0);
		light.castShadow = true;

		this.scene.add(light);

		var lightSphere = new THREE.Mesh(
				new THREE.SphereGeometry(10, 12, 6),
				new THREE.MeshBasicMaterial());
		lightSphere.position.copy(light.position);

		this.scene.add(lightSphere);

		this.geometry = new THREE.BoxGeometry(2, 3, 0.5);
		material = new THREE.MeshBasicMaterial({
				color : 0x301e10
			});
		var cubeMaterial = new THREE.MeshPhongMaterial({
				shininess : 4
			});
		cubeMaterial.color.setHex(0xAdA79b);
		cubeMaterial.specular.setRGB(0.5, 0.5, 0.5);
		cubeMaterial.ambient.copy(cubeMaterial.color);
		//cube = new THREE.Mesh(this.geometry, material);
		cube = new THREE.Mesh(this.geometry, cubeMaterial);
		cube.position.x = 0;
		cube.position.y = 0;
		cube.position.z = 0;
		this.scene.add(cube);
	}

	function animate() {
		window.requestAnimationFrame(animate);
		render();
	}
	var render = function () {
		requestAnimationFrame(render);

		cube.rotation.x = x;
		cube.rotation.y = y

			this.renderer.render(this.scene, this.camera);
	};

	function addToDOM() {
		var container = document.getElementById('container');
		var canvas = container.getElementsByTagName('canvas');
		if (canvas.length > 0) {
			container.removeChild(canvas[0]);
		}
		container.appendChild(this.renderer.domElement);
	}
	this.kickoffcube = function() {
		init();
		fillScene();
		addToDOM();
		render();
	}
	this.setRotation = function(rx,ry) {
		x = rx;
		y = ry;
	}

	// setInterval(function () {
	// if (angle < Math.PI * 2.0) {
	// angle += Math.PI / 1800.0;
	// } else {
	// angle = 0;
	// }
	// x = Math.random() * 0.1 + (Math.sin(angle) + 1) * 10;
	// y = Math.random() * 0.1 + (Math.cos(angle + 1.0) + 1) * 10;
	// }, 50);
};
