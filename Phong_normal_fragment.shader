#version 330 core
in vec3 u_color;
out vec4 FragColor;
in vec3 FragPos;
in vec2 UV;
in vec3 Normal;
in mat3 TBN;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D diffuse_second;
uniform sampler2D normal_second;

uniform vec3 u_light_dir;
uniform vec3 u_light_post;
uniform vec3 u_camera_pos;
uniform vec3 u_ambient_color;


void main()
{

	vec3 lightVector = normalize(u_light_dir);

	float distance = length(u_light_post - FragPos);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	vec3 tbnNormal = texture(texture_normal, UV).rgb + texture(normal_second, UV).rgb;
	tbnNormal = tbnNormal * 2.0 - 1.0;
	tbnNormal = normalize(TBN * tbnNormal);

	float specularStrength = 1.3;
	vec3 viewDir = normalize(u_camera_pos - FragPos);

	///phong shading
	vec3 reflectDir = reflect(-lightVector, tbnNormal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.0), 4);

	//blinn phong
	//float spec = 0.0;


	vec3 specular = specularStrength * spec * lightColor;

	vec3 diffuse = vec3(max(dot(tbnNormal, lightVector), 0.0)) * lightColor;
	float NdotL = max(dot(tbnNormal, lightVector), 0.0);
	vec3 ambient = u_ambient_color * lightColor;

	//FragColor = vec4(tbnNormal, 1.0);// texture(texture_normal, UV);
	FragColor = vec4(ambient + (diffuse + specular), 1.0) * texture(texture_diffuse, UV) + texture(diffuse_second, UV) * (1 - NdotL);


}