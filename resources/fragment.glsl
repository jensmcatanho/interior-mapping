#version 430 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
    float shininess;
};

in vec2 vs_TexCoord;

in vec3 vs_CameraDirection;
in vec3 vs_ObjectPosition;

layout(location = 6) uniform Material u_Material;

out vec4 FragColor;

vec3 upVector = vec3(0.0, 1.0, 0.0);
vec3 rightVector = vec3(1.0, 0.0, 0.0);
vec3 forwardVector = vec3(0.0, 0.0, 1.0);

float roomHeight = 0.25;
float roomWidth = 0.25;


struct Plane {
	vec3 position;
	vec3 normal;
	vec3 color;
};

struct Ray {
	vec3 direction;
	vec3 origin;
};

vec4 checkVisibility(Ray ray, Plane plane, vec4 zBuffer) {
	float distance = dot(plane.position - ray.origin, plane.normal) / dot(plane.normal, ray.direction);

	if (distance < zBuffer.w) {
		zBuffer.w = distance;
		zBuffer.rgb = plane.color;
	}

	return zBuffer;
}

void main() {
	Ray surfaceToCamera;
	surfaceToCamera.direction = normalize(vs_CameraDirection);
	surfaceToCamera.origin = vs_ObjectPosition;
	surfaceToCamera.origin += surfaceToCamera.direction * 0.0001;

	vec4 zBuffer = vec4(1.0, 1.0, 1.0, 1000000.0);

	if (dot(upVector, surfaceToCamera.direction) > 0) {
		Plane ceiling;
		ceiling.position = (ceil(surfaceToCamera.origin.y / roomHeight) * roomHeight) * upVector;
		ceiling.normal = upVector;
		ceiling.color = vec3(1.0, 0.0, 0.0);
		
		zBuffer = checkVisibility(surfaceToCamera, ceiling, zBuffer);

	} else {
		Plane floor;
		floor.position = ((ceil(surfaceToCamera.origin.y / roomHeight) - 1.0) * roomHeight) * upVector;
		floor.normal = -upVector;
		floor.color = vec3(0.0, 1.0, 0.0);
		
		zBuffer = checkVisibility(surfaceToCamera, floor, zBuffer);
	}
	
	if (dot(rightVector, surfaceToCamera.direction) > 0) {
		Plane wall;
		wall.position = (ceil(surfaceToCamera.origin.x / roomWidth) * roomWidth) * rightVector;
		wall.normal = rightVector;
		wall.color = vec3(0.0, 0.0, 1.0);
		
		zBuffer = checkVisibility(surfaceToCamera, wall, zBuffer);

	} else {
		Plane wall;
		wall.position = ((ceil(surfaceToCamera.origin.x / roomWidth) - 1.0) * roomWidth) * rightVector;
		wall.normal = -rightVector;
		wall.color = vec3(1.0, 0.1, 1.0);
		
		zBuffer = checkVisibility(surfaceToCamera, wall, zBuffer);
	}
	
	if (dot(forwardVector, surfaceToCamera.direction) > 0) {
		Plane wall;
		wall.position = (ceil(surfaceToCamera.origin.z / roomWidth) * roomWidth) * forwardVector;
		wall.normal = forwardVector;
		wall.color = vec3(0.0, 1.0, 1.0);
		
		zBuffer = checkVisibility(surfaceToCamera, wall, zBuffer);

	} else {
		Plane wall;
		wall.position = ((ceil(surfaceToCamera.origin.z / roomWidth) - 1.0) * roomWidth) * forwardVector;
		wall.normal = -forwardVector;
		wall.color = vec3(0.0, 0.0, 0.0);
		
		zBuffer = checkVisibility(surfaceToCamera, wall, zBuffer);
	}
	
	FragColor = vec4(zBuffer.rgb, 1.0); //vec4(vs_FragColor, 1.0);
	//FragColor += texture(u_Material.diffuse, vs_TexCoord);
}