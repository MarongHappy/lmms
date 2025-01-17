/*
 * BitInvader.h - declaration of class BitInvader and BSynth which
 *                         are a wavetable synthesizer
 *
 * Copyright (c) 2006-2008 Andreas Brandmaier <andy/at/brandmaier/dot/de>
 * 
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef BIT_INVADER_H
#define BIT_INVADER_H

#include "AutomatableModel.h"
#include "Instrument.h"
#include "InstrumentView.h"
#include "Graph.h"
#include "MemoryManager.h"

class oscillator;
class BitInvaderView;
class Knob;
class LedCheckBox;
class PixmapButton;

class BSynth
{
	MM_OPERATORS
public:
	BSynth( float * sample, NotePlayHandle * _nph,
			bool _interpolation, float factor, 
			const sample_rate_t _sample_rate );
	virtual ~BSynth();
	
	sample_t nextStringSample( float sample_length );


private:
	int sample_index;
	float sample_realindex;
	float* sample_shape;
	NotePlayHandle* nph;
	const sample_rate_t sample_rate;

	bool interpolation;
	
} ;

class BitInvader : public Instrument
{
	Q_OBJECT
public:
	BitInvader(InstrumentTrack * _instrument_track );
	virtual ~BitInvader();

	virtual void playNote( NotePlayHandle * _n,
						sampleFrame * _working_buffer );
	virtual void deleteNotePluginData( NotePlayHandle * _n );


	virtual void saveSettings( QDomDocument & _doc,
							QDomElement & _parent );
	virtual void loadSettings( const QDomElement & _this );

	virtual QString nodeName() const;

	virtual f_cnt_t desiredReleaseFrames() const
	{
		return( 64 );
	}

	virtual PluginView * instantiateView( QWidget * _parent );

protected slots:
	void lengthChanged();
	void samplesChanged( int, int );

	void normalize();


private:
	FloatModel  m_sampleLength;
	graphModel  m_graph;
	
	BoolModel m_interpolation;
	BoolModel m_normalize;
	
	float m_normalizeFactor;
	
	friend class BitInvaderView;
} ;



class BitInvaderView : public InstrumentViewFixedSize
{
	Q_OBJECT
public:
	BitInvaderView( Instrument * _instrument,
					QWidget * _parent );

	virtual ~BitInvaderView() {};

protected slots:
	//void sampleSizeChanged( float _new_sample_length );

	void interpolationToggled( bool value );
	void normalizeToggled( bool value );

	void sinWaveClicked();
	void triangleWaveClicked();
	void sqrWaveClicked();
	void sawWaveClicked();
	void noiseWaveClicked();
	void usrWaveClicked();
	
	void smoothClicked( void  );

private:
	virtual void modelChanged();

	Knob * m_sampleLengthKnob;
	PixmapButton * m_sinWaveBtn;
	PixmapButton * m_triangleWaveBtn;
	PixmapButton * m_sqrWaveBtn;
	PixmapButton * m_sawWaveBtn;
	PixmapButton * m_whiteNoiseWaveBtn;
	PixmapButton * m_smoothBtn;
	PixmapButton * m_usrWaveBtn;

	static QPixmap * s_artwork;

	Graph * m_graph;
	LedCheckBox * m_interpolationToggle;
	LedCheckBox * m_normalizeToggle;

} ;



#endif
