#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
uniform vec3 camPos; 

vec4 pointLight()
{
	float ambient = 0.20f;
	
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 0.005;
	float b = 0.01;
	float intensity = 1.0f/ (a*dist + dist + b * dist + 1.0f);


	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f; 
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8);
	float specular = specAmount * specularLight;
	return (texture(tex0, texCoord) * lightColor * (diffuse*intensity + ambient  ));
}

vec4 directionLight()
{
	float ambient = 0.20f;
	

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f; 
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8);
	float specular = specAmount * specularLight;
	return (texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular  ));
}

void main()
{
	// ambient lighting
	
	// outputs final color
	FragColor = directionLight() + pointLight();
}