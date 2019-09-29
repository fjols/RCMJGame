#include "Circle.h"



Circle::Circle()
{
	
	m_lines.setPrimitiveType(sf::LinesStrip);
	m_lines.resize(2);
	m_time = m_clock.getElapsedTime().asSeconds();
}

void Circle::makeCircles(sf::Vector2f pos)
{
	for (int i = 0; i < 50; i++)
	{

		fX = rand() % 800;
		fY = rand() % 800;
		float fRadius = rand() % 50 + 1;
		//float fRadius = 40.5;

		float fRandomRed = rand() % 256;
		float fRandomBlue = rand() % 256;
		float fRandomGreen = rand() % 256;

		sf::Color randomColour(fRandomRed, fRandomGreen, fRandomBlue, 128);

		std::cout << "CIRCLE: " << i << " CREATED | POSITION X: " << fX << " | POSITION Y: " << fY << std::endl;
		m_circles[i].setRadius(fRadius);
		m_circles[i].setPosition(sf::Vector2f(fX, fY));
		//m_fTheta += m_fThetaStep;
		//m_circles[i].setPosition(sf::Vector2f(pos.x + cos(m_fTheta) * fRadius, pos.y += sin(m_fTheta * cos(m_fTheta)) * fRadius * 2));
		m_circles[i].setFillColor(randomColour);

	}
}

void Circle::makeLines()
{
	for (int i = 0; i < 50; i++)
	{
		m_lines[i].position = sf::Vector2f(m_circles[i].getPosition().x, m_circles[i].getPosition().y);
		std::cout << "LINE POINT: " << i << " CREATED | POSITION X: " << m_lines[i].position.x << " | POSITION Y: " << m_lines[i].position.y << std::endl;
	}
}

void Circle::update()
{
	for (int i = 0; i < 50; i++)
	{
		m_circles[i].move(0, 0.02);
		
		// If the circles reach the bottom of the screen move them back to the top.
		if (m_circles[i].getPosition().y > 800)
		{
			m_circles[i].move(0, -850);
		}

		// Move the circles faster or slower depending on their radius size.
		if (m_circles[i].getRadius() < 10)
		{
			m_circles[i].move(0, 0.04);
		}
		else if (m_circles[i].getRadius() > 30)
		{
			m_circles[i].move(0, 0.01);
		}

	}
}

void Circle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < 50; i++)
	{
		target.draw(m_circles[i]);
		target.draw(m_lines);
	}
}

